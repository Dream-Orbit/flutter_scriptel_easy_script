import 'package:easyscript/src/types/sign_event/sign_event_cancel.dart';
import 'package:easyscript/src/types/sign_event/sign_event_coordinate.dart';
import 'package:easyscript/src/types/sign_event/sign_event_end.dart';
import 'package:easyscript/src/types/sign_event/sign_event_meta.dart';
import 'package:easyscript/src/types/sign_event/sign_event_new_stroke.dart';
import 'package:easyscript/src/types/sign_event/sign_event_start.dart';
import 'package:easyscript/src/types/sign_event/sign_event_type.dart';
import 'package:easyscript/src/types/sign_event/sign_event_unknown.dart';

export 'sign_event_cancel.dart';
export 'sign_event_coordinate.dart';
export 'sign_event_end.dart';
export 'sign_event_meta.dart';
export 'sign_event_new_stroke.dart';
export 'sign_event_start.dart';
export 'sign_event_type.dart';

class SignEvent {
  SignEventType get eventType => SignEventType.UNKNOWN;

  factory SignEvent.fromMap(Map<String, dynamic> event) {
    String eventTypeStr = event['event'] ?? 'UNKNOWN';
    eventTypeStr = eventTypeStr.toUpperCase();
    SignEventType eventType = SignEventType.values
        .firstWhere((element) => element.name == eventTypeStr);
    switch (eventType) {
      case SignEventType.SIGN_START:
        return SignEventStart.fromMap(event);
      case SignEventType.SIGN_END:
        return SignEventEnd.fromMap(event);
      case SignEventType.SIGN_CANCEL:
        return SignEventCancel.fromMap(event);
      case SignEventType.SIGN_META:
        return SignEventMeta.fromMap(event);
      case SignEventType.SIGN_COOR:
        return SignEventCoordinate.fromMap(event);
      case SignEventType.SIGN_NEW_STROKE:
        return SignEventNewStroke.fromMap(event);
      case SignEventType.UNKNOWN:
        return SignEventUnknown.fromMap(event);
    }
  }
}
