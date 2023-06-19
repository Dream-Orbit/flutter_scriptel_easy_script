# scriptouch_easyscript

Unofficial Flutter wrapper for Scriptel ScripTouch Easyscript Integration (https://scriptel.com/developers/easyscript/).

## SignaturePreview Widget
To integrate the # scriptouch_easyscript signature capturing capability, you need to add the `SignaturePreview` widget to your Widget
tree.
The `SignaturePreview` widget is a customizable signature pad integration library for capturing signatures in a Flutter
application.
It provides a canvas where users can draw their signatures either using Scriptel Signature Pad device or with touch.
The captured signature can be saved as a PNG image for further processing.

## Installation

Add the following to your `pubspec.yaml` file:

```yaml
dependencies:
   scriptouch_easyscript: ^1.0.0
```

## Usage

### Importing the SignaturePreview Widget

Import the `SignaturePreview` widget in your Dart file:

```dart
import 'package:scriptouch_easyscript/signature_preview.dart';
```

Add the `SignaturePreview` widget to your Widget tree:

```dart
SignaturePreview(
    onSignCapture: (Future<Uint8List> signImageBytes) {
      // Handle the captured signature image
      var imageBytes = await signImageBytes;
    },
);
```

## Functionality

- Allows users to draw their signature on the canvas using touch or a Scriptel Signature Pad device.
- Provides options to automatically clear the signature screen on completion or cancellation.
- Supports customization of the signature pad appearance, including screen color, ink color, and pen size.
- Enables capturing the signature as a PNG image with customizable pixel ratio.
- Supports visual guide lines for helping users in signing.
- Provides action buttons for canceling or completing the signature (in touch mode only).
- Allows programmatically capturing the signature or canceling it.
- Supports keyboard input for capturing the signature character by character.

## Key Features

### Signature Capture

The `SignaturePreview` widget allows users to draw their signatures on the canvas. It supports two modes of capturing
the signature:

1. Scriptel Signature Pad Mode: Users can connect a Scriptel Signature Pad device and draw their signature using a
   stylus.
2. Touch Mode: Users can draw their signature directly on the canvas using touch input on the device screen.

### Automatic Clearing

The widget provides options to automatically clear the signature screen when the signature is completed or canceled. By
default, the screen is cleared on completion but not on cancellation. These behaviors can be customized by setting
the `autoClearOnDone` and `autoClearOnCancel` parameters.

### Customization

The `SignaturePreview` widget allows customization of various aspects of the signature pad's appearance:

- Screen Color: The background color of the signature pad canvas.
- Ink Color: The color of the signature ink.
- Pen Size: The width of the signature stroke.
- Pixel Ratio: The pixel density of the captured signature image.

### Touch Signature and Action Buttons

The widget supports touch input for capturing signatures directly on the device screen. 
To enable touch input, set the `enableTouchSign` parameter to `true`. In touch mode, action buttons
are displayed for canceling or completing the signature. These buttons can be disabled by setting
the `enableActionButtons` parameter to `false`.

### Visual Guide Lines

The `SignaturePreview` widget provides an option to display visual guide lines to assist users in signing. These guide
lines can be enabled by setting the `enableSignGuide` parameter to `true`.

### Saving the image directly to temporary directory

The `easy_script` library provides an extension to save the captured signature image directly to the temporary directory
This extension is on `Future<Uint8List>` and can be used as follows:

```dart
var imageBytes = await signImageBytes.saveToTempDir();
```

Usage Example:
```dart
SignaturePreview(
    onSignCapture: (Future<Uint8List> signImageBytes) async {
        // Save image directly to temp dir and get the path
        var imagePath = await signImageBytes.saveToTempDir();
    },
);
```

## Example Usage

```dart
SignaturePreview(
    onSignCapture: (Future<Uint8List> signImageBytes) async {
        // Handle the captured signature image
        var path = await signImageBytes.saveToTempDir();
    },
    autoClearOnDone: false,
    autoClearOnCancel: true,
    screenColor: Colors.white,
    signColor: Colors.black,
    signStrokeWidth: 2,
    signCapturePixelRatio: 1.0,
    enableTouchSign: true,
    enableSignGuide: true,
    enableActionButtons: true,
    aspectRatio: 240/64, // Scriptel Signature pad Aspect Ratio
);
```

In the example above, the `SignaturePreview` widget is used to capture a signature. The `onSignCapture` callback is set
to handle the captured signature image. Other customization options such as screen color, ink color, and pen size are
also provided.

## License

```
BSD 3-Clause License
```
Read the [LICENSE](LICENSE) file for details.

## Changelog

Refer to the [Changelog](CHANGELOG.md) to get all release notes.