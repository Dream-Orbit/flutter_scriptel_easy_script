import 'package:easyscript/easyscript.dart';
import 'package:flutter/material.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Scriptel Plugin Demo'),
        ),
        body: Center(
          child: Padding(
            padding: const EdgeInsets.all(20),
            child: Column(
              children: [
                SignaturePreview(
                  signColor: Colors.indigo.shade700,
                  screenColor: Colors.white,
                  signStrokeWidth: 5,
                  signCapturePixelRatio: 1,
                  onSignCapture: (bytes) async {
                    var path = await bytes.saveToTempDir();
                    print(path);
                  },
                  enableTouchSign: true,
                ),
                const TextField(autofocus: true),
              ],
            ),
          ),
        ),
      ),
    );
  }
}
