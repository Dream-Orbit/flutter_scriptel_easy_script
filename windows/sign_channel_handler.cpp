//
// Created by Fighter on 05-11-2022.
//

#include <flutter/event_channel.h>
#include <flutter/standard_method_codec.h>

static std::unique_ptr<flutter::EventSink<>> _eventSink = nullptr;

void setSignEventSink(std::unique_ptr<flutter::EventSink<>>& eventSink) {
    _eventSink = std::move(eventSink);
}


void notifySignStart() {
    if (_eventSink != nullptr) {
        auto events = flutter::EncodableMap{
            { "event", "SIGN_START" },
        };
        _eventSink->Success(events);
    }
}

void notifySignMetadata(std::string model, std::string version, std::string protocol_version) {
    if (_eventSink != nullptr) {
        auto events = flutter::EncodableMap{
            { "event", "SIGN_META" },
            { "model", model },
            { "version", version},
            { "protocol_version", protocol_version},
        };
        _eventSink->Success(events);
    }
}

void notifySignCoordinate(double x, double y) {
    if (_eventSink != nullptr) {
        auto events = flutter::EncodableMap{
            { "event", "SIGN_COOR" },
            { "x", x },
            { "y", y },
        };
        _eventSink->Success(events);
    }
}

void notifySignNewStroke() {
    if (_eventSink != nullptr) {
        auto events = flutter::EncodableMap{
            { "event", "SIGN_NEW_STROKE" }
        };
        _eventSink->Success(events);
    }
}

void notifySignEnd() {
    if (_eventSink != nullptr) {
        auto events = flutter::EncodableMap{
            { "event", "SIGN_END" }
        };
        _eventSink->Success(events);
    }
}

void notifySignCancel() {
    if (_eventSink != nullptr) {
        auto events = flutter::EncodableMap{
            { "event", "SIGN_CANCEL" }
        };
        _eventSink->Success(events);
    }
}