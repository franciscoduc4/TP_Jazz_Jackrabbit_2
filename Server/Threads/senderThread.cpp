#include "senderThread.h"


SenderThread::SenderThread(Protocol& protocol, std::shared_ptr<Queue<GameTypes::Event>> eventQueue):
        protocol(protocol), eventQueue(eventQueue) {}

void SenderThread::run() {
    while (_keep_running) {
        try {
            // GameTypes::Event eventQueue->pop();
            // if (!protocol.sendMessage(status)) {
            //     break;
            // }
        } catch (const std::exception& e) {
            if (_keep_running) {
                std::cerr << "SenderThread error: " << e.what() << std::endl;
            }
        }
    }
}
