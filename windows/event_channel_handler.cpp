//
// Created by Fighter on 05-11-2022.
//

#include <flutter/event_channel.h>
#include <flutter/standard_method_codec.h>

static std::unique_ptr<flutter::EventSink<>> _eventSink = nullptr;

void notifySignatureStart() {
    if (_eventSink != nullptr) {
        auto events = flutter::EncodableMap{
            { "event", "SIGN_START" },
        };
        _eventSink->Success(events);
    }
}

void setEventSink(std::unique_ptr<flutter::EventSink<>>& eventSink) {
    _eventSink = std::move(eventSink);
}