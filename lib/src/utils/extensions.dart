import 'dart:io';
import 'dart:typed_data';

extension EasyScriptImageExtension on Future<Uint8List> {
  Future<String> saveToTempDir() async {
    Uint8List bytes = await this;
    Directory tempDir = Directory.systemTemp;
    String tempPath = tempDir.path;
    final timestamp = DateTime.now().millisecondsSinceEpoch.toString();
    String path = '$tempPath/sign_$timestamp.png';
    await File(path).writeAsBytes(bytes);
    return path;
  }
}
