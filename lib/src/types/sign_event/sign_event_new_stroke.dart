import 'package:scriptouch_easyscript/src/types/sign_event/sign_event.dart';

class SignEventNewStroke implements SignEvent {
  @override
  final SignEventType eventType = SignEventType.SIGN_NEW_STROKE;

  SignEventNewStroke._();

  factory SignEventNewStroke.fromMap(Map<String, dynamic> event) {
    return SignEventNewStroke._();
  }
}
