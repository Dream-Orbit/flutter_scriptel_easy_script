import 'package:scriptouch_easyscript/src/types/sign_event/sign_event.dart';

class SignEventCoordinate implements SignEvent {
  @override
  final SignEventType eventType = SignEventType.SIGN_COOR;
  final double x;
  final double y;

  SignEventCoordinate._({
    required this.x,
    required this.y,
  });

  factory SignEventCoordinate.fromMap(Map<String, dynamic> event) {
    double x = event['x'] ?? 0;
    double y = event['y'] ?? 0;
    return SignEventCoordinate._(x: x, y: y);
  }
}
