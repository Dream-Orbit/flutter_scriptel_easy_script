//
// Created by Fighter on 05-11-2022.
//

#ifndef EASYSCRIPT_EVENT_CHANNEL_HANDLER_H
#define EASYSCRIPT_EVENT_CHANNEL_HANDLER_H

extern void setSignEventSink(std::unique_ptr<flutter::EventSink<>>& eventSink);

extern void notifySignStart();
extern void notifySignMetadata(std::string model, std::string version, std::string protocol_version);
extern void notifySignCoordinate(double x, double y);
extern void notifySignNewStroke();
extern void notifySignEnd();
extern void notifySignCancel();

#endif //EASYSCRIPT_EVENT_CHANNEL_HANDLER_H
