import 'package:scriptouch_easyscript/src/types/sign_event/sign_event.dart';

class SignEventStart implements SignEvent {
  @override
  final SignEventType eventType = SignEventType.SIGN_START;

  SignEventStart._();

  factory SignEventStart.fromMap(Map<String, dynamic> event) {
    return SignEventStart._();
  }
}
