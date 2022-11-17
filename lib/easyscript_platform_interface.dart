import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'easyscript_method_channel.dart';

abstract class EasyscriptPlatform extends PlatformInterface {
  /// Constructs a EasyscriptPlatform.
  EasyscriptPlatform() : super(token: _token);

  static final Object _token = Object();

  static EasyscriptPlatform _instance = MethodChannelEasyscript();

  /// The default instance of [EasyscriptPlatform] to use.
  ///
  /// Defaults to [MethodChannelEasyscript].
  static EasyscriptPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [EasyscriptPlatform] when
  /// they register themselves.
  static set instance(EasyscriptPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
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
    throw UnimplementedError('setListener() has not been implemented.');
  }

  Future<void> inputCharacter(String character) {
    throw UnimplementedError('inputCharacter() has not been implemented.');
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
