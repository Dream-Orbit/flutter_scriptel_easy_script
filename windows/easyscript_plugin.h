#ifndef FLUTTER_PLUGIN_EASYSCRIPT_PLUGIN_H_
#define FLUTTER_PLUGIN_EASYSCRIPT_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace easyscript {

class EasyscriptPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  EasyscriptPlugin();

  virtual ~EasyscriptPlugin();

  // Disallow copy and assign.
  EasyscriptPlugin(const EasyscriptPlugin&) = delete;
  EasyscriptPlugin& operator=(const EasyscriptPlugin&) = delete;

 private:
  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace easyscript

#endif  // FLUTTER_PLUGIN_EASYSCRIPT_PLUGIN_H_
