#include "sender.h"

#include <iostream>
#include <memory>
#include <utility>

#include "../CommandHandlers/Lobby/lobbyCommand.h"

SenderThread::SenderThread(std::shared_ptr<Socket> socket, std::atomic<bool>& keepPlaying,
                           std::atomic<bool>& inGame, GameMonitor& gameMonitor, uint32_t playerId):
        playerId(playerId),
        serializer(socket),
        deserializer(socket),
        keepPlaying(keepPlaying),
        inGame(inGame),
        wasClosed(false),
        recvQueue(std::make_shared<Queue<std::unique_ptr<CommandDTO>>>()),
        receiver(socket, keepPlaying, inGame, playerId, recvQueue),
        gameMonitor(gameMonitor) {
    sendQueue = std::make_shared<Queue<std::unique_ptr<DTO>>>();
    std::cout << "[SERVER SENDER] SenderThread initialized" << std::endl;
}

void SenderThread::run() {
    bool wasClosed = false;
    std::cout << "[SERVER SENDER] Sender started" << std::endl;
    serializer.sendId(playerId, wasClosed);

    while (keepPlaying) {
        std::cout << "[SERVER SENDER] Running lobby" << std::endl;
        runLobby(wasClosed);
        while (inGame) {
            try {
                std::unique_ptr<DTO> dto = sendQueue->pop();
                std::cout << "[SERVER SENDER] DTO popped from sendQueue" << std::endl;
                auto gameDTO = dynamic_cast<GameDTO*>(dto.get());
                dto.release();
                std::cout << "[SERVER SENDER] Sending gameDTO" << std::endl;
                serializer.sendGameDTO(std::unique_ptr<GameDTO>(gameDTO), wasClosed);
            } catch (const std::exception& e) {
                std::cerr << "[SERVER SENDER] Exception in game: " << e.what() << std::endl;
                if (wasClosed) {
                    std::cout << "[SERVER SENDER] Socket was closed, exiting game" << std::endl;
                    return;
                }
            }
        }
    }
    std::cout << "[SERVER SENDER] Exiting run" << std::endl;
}

void SenderThread::runLobby(bool& wasClosed) {
    while (keepPlaying && !inGame) {
        try {
            std::cout << "[SERVER SENDER LOBBY] Waiting for command" << std::endl;
            std::unique_ptr<CommandDTO> command = deserializer.getCommand(wasClosed, playerId);
            if (command == nullptr) {
                std::cout << "[SERVER SENDER LOBBY] No command received, continuing" << std::endl;
                continue;
            }
            std::cout << "[SERVER SENDER LOBBY] Command received" << std::endl;

            auto handler = LobbyCommandHandler::createHandler(std::move(command));
            handler->execute(gameMonitor, std::ref(inGame), recvQueue, sendQueue);
            std::cout << "[SERVER SENDER LOBBY] Command executed" << std::endl;

            auto dto = sendQueue->pop();
            auto commandDTO = dynamic_cast<CommandDTO*>(dto.get());
            dto.release();
            std::cout << "[SERVER SENDER LOBBY] Sending command DTO" << std::endl;
            serializer.sendCommand(std::unique_ptr<CommandDTO>(commandDTO), wasClosed);
            std::cout << "[SERVER SENDER LOBBY] Command ACK sent" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "[SERVER SENDER LOBBY] Exception: " << e.what() << std::endl;
            if (wasClosed) {
                std::cout << "[SERVER SENDER LOBBY] Socket was closed, exiting lobby" << std::endl;
                return;
            }
        }
    }
    std::cout << "[SERVER SENDER LOBBY] Out of lobby" << std::endl;
    receiver.start();
}
