import 'package:scriptouch_easyscript/src/types/sign_event/sign_event.dart';

class SignEventEnd implements SignEvent {
  @override
  final SignEventType eventType = SignEventType.SIGN_END;

  SignEventEnd._();

  factory SignEventEnd.fromMap(Map<String, dynamic> event) {
    return SignEventEnd._();
  }
}
