import 'package:easyscript/src/types/sign_event/sign_event.dart';
import 'package:easyscript/src/types/sign_event/sign_event_type.dart';

class SignEventMeta implements SignEvent {
  @override
  final SignEventType eventType = SignEventType.SIGN_META;
  final String model;
  final String version;
  final String protocolVersion;

  SignEventMeta._({
    required this.model,
    required this.version,
    required this.protocolVersion,
  });

  factory SignEventMeta.fromMap(Map<String, dynamic> event) {
    String model = event['model'] ?? 'UNKNOWN';
    String version = event['version'] ?? 'UNKNOWN';
    String protocolVersion = event['protocolVersion'] ?? 'UNKNOWN';
    return SignEventMeta._(
      model: model,
      version: version,
      protocolVersion: protocolVersion,
    );
  }
}
