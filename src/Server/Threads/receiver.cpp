#include "receiver.h"

#include <iostream>
#include <memory>
#include <utility>

#include "../CommandHandlers/Lobby/lobbyCommand.h"

ReceiverThread::ReceiverThread(const std::shared_ptr<Socket>& socket,
                               std::atomic<bool>& keepPlaying, std::atomic<bool>& inGame,
                               uint8_t playerId, GameMonitor& gameMonitor,
                               const std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>>& recvQueue,
                               const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue):
        playerId(playerId),
        serializer(socket, keepPlaying, inGame),
        deserializer(socket, keepPlaying, inGame),
        keepPlaying(keepPlaying),
        inGame(inGame),
        gameMonitor(gameMonitor),
        recvQueue(recvQueue),
        sendQueue(sendQueue) {
    std::cout << "[SERVER RECEIVER] ReceiverThread initialized" << std::endl;
}

void ReceiverThread::runLobby() {
    if (inGame.load())
        return;

    std::cout << "[SERVER RECEIVER LOBBY] Waiting for command" << std::endl;
    std::unique_ptr<CommandDTO> command = deserializer.getCommand(playerId);
    if (command == nullptr) {
        std::cout << "[SERVER RECEIVER LOBBY] No command received, continuing" << std::endl;
        return;
    }
    if (inGame.load())
        return;

    std::cout << "[SERVER RECEIVER LOBBY] Command received" << std::endl;

    auto handler = LobbyCommandHandler::createHandler(std::move(command));
    std::cout << "[SERVER RECEIVER LOBBY] Handler created" << std::endl;
    if (inGame.load())
        return;

    handler->execute(gameMonitor, inGame, sendQueue);


    std::cout << "[SERVER RECEIVER LOBBY] Command executed" << std::endl;
}

void ReceiverThread::runGame() {
    std::cout << "[SERVER RECEIVER] Waiting to receive command" << std::endl;
    std::unique_ptr<CommandDTO> commandDTO = deserializer.getCommand(playerId);
    if (commandDTO) {
        std::cout << "[SERVER RECEIVER] Command received, pushing to recvQueue" << std::endl;
        gameMonitor.getPlayerGameQueue(playerId)->push(std::move(commandDTO));
    } else {
        std::cout << "[SERVER RECEIVER] No command received (null commandDTO)" << std::endl;
    }
}

void ReceiverThread::run() {
    std::cout << "[SERVER RECEIVER] Receiver thread started" << std::endl;
    std::cout << "[SERVER RECEIVER] Running Lobby..." << std::endl;
    while (keepPlaying.load() && !inGame.load()) {
        try {
            this->runLobby();
        } catch (const std::exception& e) {
            std::cerr << "[SERVER RECEIVER] Exception: " << e.what() << std::endl;
            if (!inGame.load() || !keepPlaying.load()) {
                std::cout << "[SERVER RECEIVER] Socket was closed, exiting receiver thread"
                          << std::endl;
                return;
            }
        }
    }
    std::cout << "[SERVER RECEIVER] Running Game..." << std::endl;
    while (keepPlaying.load() && inGame.load()) {
        try {
            this->runGame();
        } catch (const std::exception& e) {
            std::cerr << "[SERVER RECEIVER] Exception: " << e.what() << std::endl;
            if (!inGame.load() || !keepPlaying.load()) {
                std::cout << "[SERVER RECEIVER] Socket was closed, exiting receiver thread"
                          << std::endl;
                return;
            }
        }
    }
    std::cout << "[SERVER RECEIVER] Receiver thread exiting" << std::endl;
}
