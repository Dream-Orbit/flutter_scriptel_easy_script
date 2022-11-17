#include "easyscript_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/event_channel.h>
#include <flutter/event_stream_handler_functions.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#pragma comment(lib, "scriptel-easyscript.lib")

extern "C" {
#include "scriptel/scriptel-easyscript.h"
}

#include <memory>
#include <sstream>

#include "sign_channel_handler.h"

namespace easyscript {

	// static
	void EasyscriptPlugin::RegisterWithRegistrar(
		flutter::PluginRegistrarWindows* registrar) {
		auto channel =
			std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
				registrar->messenger(), "easyscript",
				&flutter::StandardMethodCodec::GetInstance());

		auto plugin = std::make_unique<EasyscriptPlugin>();

		channel->SetMethodCallHandler(
			[plugin_pointer = plugin.get()](const auto& call, auto result) {
				plugin_pointer->HandleMethodCall(call, std::move(result));
			});

		/* Setup signature event handler & channel */

		auto eventHandler = std::make_unique<flutter::StreamHandlerFunctions<>>(
			[](const flutter::EncodableValue* arguments, std::unique_ptr<flutter::EventSink<>>&& events)
			-> std::unique_ptr<flutter::StreamHandlerError<>> {
				setSignEventSink(events);
				return nullptr;
			},
			[](const flutter::EncodableValue* arguments)
				-> std::unique_ptr<flutter::StreamHandlerError<>> {
				return nullptr;
			});

		auto eventChannel = std::make_unique<flutter::EventChannel<flutter::EncodableValue>>(
			registrar->messenger(), "easyscript_sign_channel",
			&flutter::StandardMethodCodec::GetInstance());

		eventChannel->SetStreamHandler(std::move(eventHandler));

		registrar->AddPlugin(std::move(plugin));
	}

	static int done;

	void listener(streaming_event_data* sd) {

		switch (sd->type) {
		case CBT_METADATA:
			notifySignStart();
			notifySignMetadata(sd->meta_data.model, sd->meta_data.version, sd->meta_data.protocol_version);

			break;
		case CBT_COORDINATE:
			notifySignCoordinate(sd->coordinate.x, sd->coordinate.y);

			break;
		case CBT_NEWSTROKE:
			notifySignNewStroke();
			break;
		case CBT_END_OF_SIGNATURE:
			notifySignEnd();
			break;
		case CBT_CANCEL:
			notifySignCancel();
			break;
		case CBT_CARD_DATA:
			scriptel_print_cardswipe(&sd->card_swipe);
			scriptel_free_cardswipe(&sd->card_swipe);
			break;
		}
	}

	EasyscriptPlugin::EasyscriptPlugin() {
		scriptel_add_event_listener(listener);
	}

	EasyscriptPlugin::~EasyscriptPlugin() {}

	void EasyscriptPlugin::HandleMethodCall(
		const flutter::MethodCall<flutter::EncodableValue>& method_call,
		std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {

		if (method_call.method_name().compare("getPlatformVersion") == 0) {

			std::ostringstream version_stream;
			version_stream << "Windows ";
			if (IsWindows10OrGreater()) {
				version_stream << "10+";
			}
			else if (IsWindows8OrGreater()) {
				version_stream << "8";
			}
			else if (IsWindows7OrGreater()) {
				version_stream << "7";
			}
			result->Success(flutter::EncodableValue(version_stream.str()));

		}
		else if (method_call.method_name().compare("input_character") == 0) {

			const auto* arguments = std::get_if<flutter::EncodableMap>(method_call.arguments());
			std::string input;

			if (arguments) {
				auto input_it = arguments->find(flutter::EncodableValue("character"));
				if (input_it != arguments->end()) {
					input = std::get<std::string>(input_it->second);
					scriptel_keyboard_parse_char(&STN_SIGNATURE_PROTOCOL, input[0]);
				}
			}

			result->Success(flutter::EncodableValue());

		}
		else {
			result->NotImplemented();
		}
	}

}  // namespace easyscript