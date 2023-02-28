import 'dart:typed_data';
import 'dart:ui' as ui;

import 'package:easyscript/easyscript.dart';
import 'package:easyscript/src/types/constants.dart';
import 'package:easyscript/src/types/sign_point.dart';
import 'package:easyscript/src/widgets/scriptel_button.dart';
import 'package:easyscript/src/widgets/signature_preview/sign_canvas.dart';
import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';

class SignaturePreview extends StatelessWidget {
  final Easyscript _plugin = Easyscript();
  final FocusNode _focusNode = FocusNode();
  final ValueNotifier<Color> _outlineColor = ValueNotifier(Colors.grey);
  final ValueNotifier<bool> _isFocused = ValueNotifier(false);
  final ValueNotifier<bool> _isNewStroke = ValueNotifier(false);
  final ValueNotifier<SignaturePreviewWidgetState> _state =
      ValueNotifier(SignaturePreviewWidgetState.IDLE);
  final ValueNotifier<List<SignPoint>> _drawnSign = ValueNotifier([]);
  final GlobalKey _signGlobalKey = GlobalKey();

  /// Returns drawn signature as png bytes image, when done is pressed on scriptel pad or on touch
  final void Function(Future<Uint8List> signImageBytes)? onSignCapture;

  /// Automatically clears signature screen when done is pressed
  final bool autoClearOnDone;

  /// Automatically clears signature screen when cancel is pressed
  final bool autoClearOnCancel;

  /// The screen colour of signature screen
  final Color screenColor;

  /// The ink colour of signature
  final Color signColor;

  /// The pen size of signature
  final double signStrokeWidth;

  /// The pixel ratio of image to be rendered with [onSignCapture]
  final double signCapturePixelRatio;

  /// Enables signature by touch, also enables
  final bool enableTouchSign;

  /// Enables visual guide line for signing
  final bool enableSignGuide;

  /// Aspect ratio of signature pad, defaults to 240:64 which is scriptel signature pad's ratio
  final double aspectRatio;

  /// A Widget that captures Signature with Scriptel Signature Pad device or touch
  SignaturePreview({
    Key? key,
    this.onSignCapture,
    this.autoClearOnDone = false,
    this.autoClearOnCancel = true,
    this.screenColor = Colors.white,
    this.signColor = primaryColor,
    this.signStrokeWidth = 2,
    this.signCapturePixelRatio = 1.0,
    this.enableTouchSign = false,
    this.enableSignGuide = false,
    this.aspectRatio = DEVICE_ASPECT_RATIO,
  }) : super(key: key) {
    _focusNode.addListener(() => _isFocused.value = _focusNode.hasFocus);
    _plugin.setListener(
      onSignCoordinate: _registerSignCoordinate,
      onSignCancel: _registerSignCancel,
      onSignEnd: _registerSignComplete,
      onSignStart: _registerNewSignStart,
      onNewStroke: _registerNewStroke,
      onSignMeta: (model, version, protocolVersion) {},
    );
  }

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
      onTap: () {
        FocusScope.of(context).requestFocus(_focusNode);
      },
      onTapDown: (details) {
        if (_state.value != SignaturePreviewWidgetState.SIGNING)
          _registerNewSignStart();
        _registerNewStroke();
      },
      onPanEnd: (details) {
        _registerNewStroke();
      },
      onPanUpdate: (details) {
        if (!enableTouchSign ||
            _state.value != SignaturePreviewWidgetState.SIGNING) return;

        var signPadWidth = _signGlobalKey.currentContext?.size?.width ?? 1;
        var signPadHeight = _signGlobalKey.currentContext?.size?.height ?? 1;

        var fx =
            (details.localPosition.dx / signPadWidth) * DEVICE_SCREEN_WIDTH;
        var fy =
            (details.localPosition.dy / signPadHeight) * DEVICE_SCREEN_HEIGHT;

        _registerSignCoordinate(fx, fy);
      },
      child: RawKeyboardListener(
        autofocus: true,
        onKey: (e) {
          if (e.character != null) {
            _plugin.input(e.character!);
          }
        },
        focusNode: _focusNode,
        child: Stack(
          children: [
            ValueListenableBuilder<Color>(
              valueListenable: _outlineColor,
              builder: (context, outlineColorValue, child) {
                return AspectRatio(
                  aspectRatio: aspectRatio,
                  child: Container(
                    clipBehavior: Clip.hardEdge,
                    decoration: BoxDecoration(
                      border: Border.all(
                        color: outlineColorValue,
                        width: 2,
                      ),
                    ),
                    child: child!,
                  ),
                );
              },
              child: ValueListenableBuilder<List<SignPoint>>(
                valueListenable: _drawnSign,
                builder: (context, signPointsList, child) {
                  return RepaintBoundary(
                    key: _signGlobalKey,
                    child: CustomPaint(
                      painter: SignCanvas(
                        signPoints: signPointsList,
                        screenColor: screenColor,
                        strokeColor: signColor,
                        strokeWidth: signStrokeWidth,
                      ),
                    ),
                  );
                },
              ),
            ),
            if (enableTouchSign)
              Positioned(
                top: 10,
                right: 10,
                child: Row(
                  children: [
                    ScriptelButton(
                      onTap: _registerSignCancel,
                      label: 'CANCEL',
                    ),
                    const SizedBox(width: 10),
                    ScriptelButton(
                      onTap: () {
                        if (_drawnSign.value.isEmpty) {
                          _registerSignCancel();
                        } else {
                          _registerSignComplete();
                        }
                      },
                      label: 'OK',
                    ),
                  ],
                ),
              ),
            if (enableSignGuide)
              Positioned(
                bottom: 20,
                left: 20,
                child: Row(
                  crossAxisAlignment: CrossAxisAlignment.end,
                  children: [
                    const Icon(Icons.close_sharp, color: Colors.grey),
                    const SizedBox(width: 5),
                    SizedBox(
                      width: MediaQuery.of(context).size.width - 114,
                      child: const Divider(color: Colors.grey, thickness: 2),
                    ),
                  ],
                ),
              )
          ],
        ),
      ),
    );
  }

  /// When this method is called, the signature is registered as complete and eventually [onSignCapture] is called
  Future<void> captureSignature() async {
    await _registerSignComplete();
  }

  /// When this method is called, the signature is registered as cancelled
  void cancelSignature() {
    _registerSignCancel();
  }

  Future<void> _capture() async {
    if (onSignCapture == null) return;
    Future<Uint8List> captureProcess = Future(() async {
      RenderRepaintBoundary? boundary = _signGlobalKey.currentContext!
          .findRenderObject() as RenderRepaintBoundary?;
      ui.Image image =
          await boundary!.toImage(pixelRatio: signCapturePixelRatio);
      ByteData? byteData =
          await image.toByteData(format: ui.ImageByteFormat.png);
      Uint8List pngBytes = byteData!.buffer.asUint8List();
      return pngBytes;
    });
    onSignCapture?.call(captureProcess);
  }

  void _registerSignCoordinate(double x, double y) {
    _state.value = SignaturePreviewWidgetState.SIGNING;
    _drawnSign.value.add(SignPoint(x: x, y: y, newStroke: _isNewStroke.value));
    _isNewStroke.value = false;
    _drawnSign.notifyListeners();
  }

  void _registerNewSignStart() {
    _state.value = SignaturePreviewWidgetState.SIGNING;
    _isNewStroke.value = true;
    _drawnSign.value = [];
    _outlineColor.value = _getOutlineColor();
  }

  Future<void> _registerSignComplete() async {
    _state.value = SignaturePreviewWidgetState.DONE;
    _outlineColor.value = _getOutlineColor();
    await _capture();
    if (autoClearOnDone) _clearSign();
  }

  void _registerSignCancel() {
    _state.value = SignaturePreviewWidgetState.CANCELLED;
    if (autoClearOnCancel) _clearSign();
    _outlineColor.value = _getOutlineColor();
  }

  void _registerNewStroke() {
    _state.value = SignaturePreviewWidgetState.SIGNING;
    _isNewStroke.value = true;
    _outlineColor.value = _getOutlineColor();
  }

  void _clearSign() {
    _isNewStroke.value = true;
    _drawnSign.value = [];
    _outlineColor.value = _getOutlineColor();
  }

  Color _getOutlineColor() {
    switch (_state.value) {
      case SignaturePreviewWidgetState.IDLE:
        return _isFocused.value ? focusedColor : idleColor;
      case SignaturePreviewWidgetState.SIGNING:
        return focusedColor;
      case SignaturePreviewWidgetState.DONE:
        return acceptedColor;
      case SignaturePreviewWidgetState.CANCELLED:
        return _isFocused.value ? Colors.red : idleColor;
    }
  }

  Color get focusedColor => primaryColor;

  Color get idleColor => Colors.grey;

  Color get acceptedColor => Colors.green;
}

enum SignaturePreviewWidgetState {
  IDLE,
  SIGNING,
  DONE,
  CANCELLED,
}
