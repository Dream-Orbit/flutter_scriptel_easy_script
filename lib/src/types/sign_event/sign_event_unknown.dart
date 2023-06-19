import 'package:scriptouch_easyscript/src/types/sign_event/sign_event.dart';

class SignEventUnknown implements SignEvent {
  @override
  final SignEventType eventType = SignEventType.UNKNOWN;

  SignEventUnknown._();

  factory SignEventUnknown.fromMap(Map<String, dynamic> event) {
    return SignEventUnknown._();
  }
}
