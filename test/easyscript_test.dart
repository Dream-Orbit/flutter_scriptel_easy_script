import 'package:easyscript/easyscript.dart';
import 'package:easyscript/easyscript_method_channel.dart';
import 'package:easyscript/easyscript_platform_interface.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockEasyscriptPlatform
    with MockPlatformInterfaceMixin
    implements EasyscriptPlatform {
  @override
  Future<String?> getPlatformVersion() => Future.value('42');

  @override
  void setListener({
    void Function()? onSignStart,
    void Function()? onSignEnd,
    void Function()? onSignCancel,
    void Function()? onNewStroke,
    void Function(double x, double y)? onSignCoordinate,
    void Function(String model, String version, String protocolVersion)?
        onSignMeta,
  }) {
    // TODO: implement setListener
  }

  @override
  Future<void> inputCharacter(String character) async {
    // TODO: implement inputCharacter
  }
}

void main() {
  final EasyscriptPlatform initialPlatform = EasyscriptPlatform.instance;

  test('$MethodChannelEasyscript is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelEasyscript>());
  });

  test('getPlatformVersion', () async {
    Easyscript easyscriptPlugin = Easyscript();
    MockEasyscriptPlatform fakePlatform = MockEasyscriptPlatform();
    EasyscriptPlatform.instance = fakePlatform;

    expect(await easyscriptPlugin.getPlatformVersion(), '42');
  });
}
