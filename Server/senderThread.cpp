#include "senderThread.h"


ClientSender::ClientSender(Protocol& protocol, std::shared_ptr<Queue<GameTypes::Event>> eventQueue):
        protocol(protocol), eventQueue(eventQueue) {}

void ClientSender::run() {
    while (_keep_running) {
        try {
            GameTypes::Event eventQueue->pop();
            if (!protocol.sendGameStateUpdate(status)) {
                break;
            }
        } catch (const std::exception& e) {
            if (_keep_running) {
                std::cerr << "ClientSender error: " << e.what() << std::endl;
            }
        }
    }
}