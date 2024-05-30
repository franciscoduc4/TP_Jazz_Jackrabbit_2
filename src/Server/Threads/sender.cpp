#include "sender.h"


SenderThread::SenderThread(std::shared_ptr<Socket> socket, std::atomic<bool>& keepPlaying,
                           std::atomic<bool>& inGame, GameMonitor& gameMonitor, uint8_t id):
        id(id),
        serializer(socket),
        deserializer(socket),
        keepPlaying(keepPlaying),
        inGame(inGame),
        sendQueue(),
        receiver(socket, keepPlaying, inGame, sendQueue, id),
        gameMonitor(gameMonitor),
        receiverQueue(gameMonitor.getReceiverQueue()) {}

void SenderThread::run() {
    serializer.sendId(id);
    while (keepPlaying) {
        runLobby();
        try {
            while () } catch (const std::exception& e) {
            if (_keep_running) {
                std::cerr << "SenderThread error: " << e.what() << std::endl;
            }
        }
    }
}

void SenderThread::runLobby() {
    while (keepPlaying) {
        try {
            CommandDTO command = deserializer.receiveCommand(&wasClosed, id);

            if (command->getCommand() == Command::CREATE_GAME) {
                CreateGameDTO createGame =
            }
        }
    }
}
