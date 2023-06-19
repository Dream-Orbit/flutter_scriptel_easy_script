import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:scriptouch_easyscript/src/types/sign_event/sign_event.dart';

import 'easyscript_platform_interface.dart';

/// An implementation of [EasyscriptPlatform] that uses method channels.
class MethodChannelEasyscript extends EasyscriptPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('easyscript');

  final signEventChannel = const EventChannel('easyscript_sign_channel');

  MethodChannelEasyscript() {
    signEventChannel.receiveBroadcastStream().listen(_signEventListener);
  }

  @override
  Future<String?> getPlatformVersion() async {
    final version =
        await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }

  @override
  Future<void> inputCharacter(String character) async {
    methodChannel
        .invokeMethod<void>('input_character', {'character': character});
  }

  // --------------------  Event Listeners  --------------------------- //
  void Function()? _onSignStart;
  void Function()? _onSignEnd;
  void Function()? _onSignCancel;
  void Function()? _onNewStroke;
  void Function(double x, double y)? _onSignCoordinate;
  void Function(String model, String version, String protocolVersion)?
      _onSignMeta;

  @override
  void setListener({
    void Function()? onSignStart,
    void Function()? onSignEnd,
    void Function()? onSignCancel,
    void Function()? onNewStroke,
    void Function(double x, double y)? onSignCoordinate,
    void Function(String model, String version, String protocolVersion)?
        onSignMeta,
  }) {
    _onSignStart = onSignStart;
    _onSignEnd = onSignEnd;
    _onSignCancel = onSignCancel;
    _onNewStroke = onNewStroke;
    _onSignCoordinate = onSignCoordinate;
    _onSignMeta = onSignMeta;
  }

  void _signEventListener(data) {
    SignEvent event = SignEvent.fromMap(Map.castFrom(data));
    switch (event.eventType) {
      case SignEventType.SIGN_START:
        _onSignStart?.call();
        break;
      case SignEventType.SIGN_END:
        _onSignEnd?.call();
        break;
      case SignEventType.SIGN_CANCEL:
        _onSignCancel?.call();
        break;
      case SignEventType.SIGN_META:
        SignEventMeta metaEvent = (event as SignEventMeta);
        _onSignMeta?.call(
            metaEvent.model, metaEvent.version, metaEvent.protocolVersion);
        break;
      case SignEventType.SIGN_COOR:
        SignEventCoordinate coorEvent = (event as SignEventCoordinate);
        _onSignCoordinate?.call(coorEvent.x, coorEvent.y);
        break;
      case SignEventType.SIGN_NEW_STROKE:
        _onNewStroke?.call();
        break;
      case SignEventType.UNKNOWN:
        break;
    }
  }
}
