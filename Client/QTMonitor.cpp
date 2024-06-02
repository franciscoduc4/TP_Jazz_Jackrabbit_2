#include "./QTMonitor.h"

QTMonitor::QTMonitor(SenderThread& sender, ReceiverThread& receiver) : 
    sender(sender), receiver(receiver), serializer() {}

void QTMonitor::send_message(const std::string& msg) {
    std::lock_guard<std::mutex> lock(this->mutex);
    ProtocolMessage parsedMsg = this->serializer.parseSendMessage(msg);
    this->sender.push_message(parsedMsg);
}

LobbyMessage QTMonitor::recv_message() {
    std::lock_guard<std::mutex> lock(this->mutex);
    return this->receiver.recv_msg();
}
