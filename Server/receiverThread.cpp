#include "receiverThread.h"


ClientReceiver::ClientReceiver(Protocol& protocol, Queue<GameTypes::Action>& gameQueue):
        protocol(protocol), gameQueue(gameQueue) {}

void ClientReceiver::run() {
    while (_keep_running) {
        try {
            GameTypes::Action command;
            if (!protocol.receiveCommand(command)) {
                break;
            }
            gameQueue.push(command);
        } catch (const std::exception& e) {
            if (_keep_running) {
                std::cerr << "ClientReceiver error: " << e.what() << std::endl;
            }
        }
    }
}