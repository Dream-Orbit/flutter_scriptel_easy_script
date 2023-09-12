#include "include/scriptouch_easyscript/easyscript_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "easyscript_plugin.h"

void EasyscriptPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  easyscript::EasyscriptPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
