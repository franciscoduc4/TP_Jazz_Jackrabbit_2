#include "senderThread.h"


SenderThread::SenderThread(Protocol& protocol, std::shared_ptr<Queue<std::string>> senderQueue):
        protocol(protocol), senderQueue(senderQueue) {}

void SenderThread::run() {
    while (_keep_running) {
        try {
            // std::string senderQueue->pop();
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
