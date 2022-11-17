import 'package:easyscript/src/types/sign_event/sign_event.dart';
import 'package:easyscript/src/types/sign_event/sign_event_type.dart';

class SignEventCancel implements SignEvent {
  @override
  final SignEventType eventType = SignEventType.SIGN_CANCEL;

  SignEventCancel._();

  factory SignEventCancel.fromMap(Map<String, dynamic> event) {
    return SignEventCancel._();
  }
}
