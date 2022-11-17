import 'package:easyscript/src/types/constants.dart';
import 'package:easyscript/src/types/sign_point.dart';
import 'package:flutter/material.dart';

class SignCanvas extends CustomPainter {
  late final List<SignPoint> _signPoints;
  late final Color strokeColor;
  late final double strokeWidth;
  late final Color screenColor;

  Offset _lastPoint = const Offset(0, 0);

  SignCanvas({
    required List<SignPoint> signPoints,
    this.strokeWidth = 1.5,
    this.strokeColor = Colors.black,
    this.screenColor = Colors.white,
  }) {
    _signPoints = List.of(signPoints);
  }

  @override
  void paint(Canvas canvas, Size size) {
    // Draw background
    final canvasPaint = Paint()
      ..style = PaintingStyle.fill
      ..color = screenColor;
    canvas.drawRect(
      Rect.fromLTWH(0, 0, size.width, size.height),
      canvasPaint,
    );

    // Draw lines with points
    final stokePaint = Paint()
      ..style = PaintingStyle.stroke
      ..strokeCap = StrokeCap.round
      ..strokeWidth = strokeWidth
      ..color = strokeColor;

    for (var point in _signPoints) {
      Offset thisPoint = getResizedPosition(size, point.x, point.y);
      if (point.newStroke) {
        _lastPoint = thisPoint;
      }
      canvas.drawLine(_lastPoint, thisPoint, stokePaint);
      _lastPoint = thisPoint;
    }
  }

  Offset getResizedPosition(Size canvasSize, double x, double y) {
    double sizedX = (x / DEVICE_SCREEN_WIDTH) * canvasSize.width;
    double sizedY = (y / DEVICE_SCREEN_HEIGHT) * canvasSize.height;
    return Offset(sizedX, sizedY);
  }

  @override
  bool shouldRepaint(SignCanvas oldDelegate) =>
      _signPoints != oldDelegate._signPoints;
}
