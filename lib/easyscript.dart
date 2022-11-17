import 'easyscript_platform_interface.dart';

export 'src/utils/utils.dart';
export 'src/widgets/signature_preview/signature_preview.dart';

class Easyscript {
  Future<String?> getPlatformVersion() {
    return EasyscriptPlatform.instance.getPlatformVersion();
  }

  void setListener({
    void Function()? onSignStart,
    void Function()? onSignEnd,
    void Function()? onSignCancel,
    void Function()? onNewStroke,
    void Function(double x, double y)? onSignCoordinate,
    void Function(String model, String version, String protocolVersion)?
        onSignMeta,
  }) {
    EasyscriptPlatform.instance.setListener(
      onSignCoordinate: onSignCoordinate,
      onSignStart: onSignStart,
      onSignEnd: onSignEnd,
      onSignCancel: onSignCancel,
      onNewStroke: onNewStroke,
      onSignMeta: onSignMeta,
    );
  }

  void input(String character) {
    EasyscriptPlatform.instance.inputCharacter(character);
  }
}
