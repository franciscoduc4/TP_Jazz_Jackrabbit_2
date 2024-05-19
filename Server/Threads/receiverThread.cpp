#include "receiverThread.h"


ReceiverThread::ReceiverThread(Protocol& protocol, Queue<GameTypes::Action>& gameQueue):
        protocol(protocol), gameQueue(gameQueue) {}

void ReceiverThread::run() {
    while (_keep_running) {
        try {
            // GameTypes::Action command;
            // if (!protocol.receiveCommand(command)) {
            //     break;
            // }
            // gameQueue.push(command);
        } catch (const std::exception& e) {
            if (_keep_running) {
                std::cerr << "ReceiverThread error: " << e.what() << std::endl;
            }
        }
    }
}