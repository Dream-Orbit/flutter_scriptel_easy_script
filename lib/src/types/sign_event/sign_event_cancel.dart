import 'package:scriptouch_easyscript/src/types/sign_event/sign_event.dart';

class SignEventCancel implements SignEvent {
  @override
  final SignEventType eventType = SignEventType.SIGN_CANCEL;

  SignEventCancel._();

  factory SignEventCancel.fromMap(Map<String, dynamic> event) {
    return SignEventCancel._();
  }
}
