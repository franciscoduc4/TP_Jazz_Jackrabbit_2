#include "./QTMonitor.h"

QTMonitor::QTMonitor(Protocol& protocol, SenderThread& sender, ReceiverThread& receiver) : 
    protocol(protocol), sender(sender), receiver(receiver) {}

QTMonitor::sendMessage(const LobbyMessage& msg) {
    std::lock_guard<std::mutex> lock(this->mutex);
    ProtocolMessage parsedMsg = this->serializer.parseSendMessage(msg);
    this->sender.push_message(parsedMsg);
}
