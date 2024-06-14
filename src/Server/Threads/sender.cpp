#include "sender.h"
#include <memory>
#include <utility>
#include "../CommandHandlers/Lobby/lobbyCommand.h"

SenderThread::SenderThread(std::shared_ptr<Socket> socket, std::atomic<bool>& keepPlaying,
                           std::atomic<bool>& inGame, GameMonitor& gameMonitor, uint32_t playerId,
                           std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue):
        playerId(playerId),
        serializer(socket),
        deserializer(socket),
        keepPlaying(keepPlaying),
        inGame(inGame),
        wasClosed(false),
        sendQueue(sendQueue),
        recvQueue(std::make_shared<Queue<std::unique_ptr<CommandDTO>>>()),
        receiver(socket, keepPlaying, inGame, gameMonitor, playerId, recvQueue),
        gameMonitor(gameMonitor) {}

void SenderThread::run() {
    bool wasClosed = false;
    std::cout << "Sender started" << std::endl;
    serializer.sendId(playerId, wasClosed);

    while (keepPlaying) {
        runLobby(wasClosed);
        while (inGame) {
            std::cout << "ingame" << std::endl;
            try {
                std::unique_ptr<DTO> dto = sendQueue->pop();
                std::cout << "TEST - DTO POPPED" << std::endl;
                auto gameDTO = dynamic_cast<GameDTO*>(dto.get());
                dto.release();
                serializer.sendGameDTO(std::unique_ptr<GameDTO>(gameDTO), wasClosed);
            } catch (const std::exception& e) {
                if (wasClosed) {
                    return;
                }
            }
        }
    }
}

void SenderThread::runLobby(bool& wasClosed) {
    while (keepPlaying && !inGame) {
        try {
            std::cout << "Waiting for command" << std::endl;
            std::unique_ptr<CommandDTO> command = deserializer.getCommand(wasClosed, playerId);
            if (command == nullptr) {
                continue;
            }
            auto handler = LobbyCommandHandler::createHandler(std::move(command));
            handler->execute(gameMonitor, std::ref(inGame), recvQueue, sendQueue);

            // Send response back to client
            auto dto = sendQueue->pop();
            auto commandDTO = dynamic_cast<CommandDTO*>(dto.get());
            dto.release();
            serializer.sendCommand(std::unique_ptr<CommandDTO>(commandDTO), wasClosed);
            std::cout << "Command ACK sent" << std::endl;
        } catch (const std::exception& e) {
            if (wasClosed) {
                return;
            }
        }
    }
    receiver.start();
}
