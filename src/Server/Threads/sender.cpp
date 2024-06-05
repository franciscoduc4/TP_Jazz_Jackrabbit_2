#include "sender.h"

#include <memory>
#include <utility>

#include "../CommandHandlers/Lobby/lobbyCommand.h"

SenderThread::SenderThread(std::shared_ptr<Socket> socket, std::atomic<bool>& keepPlaying,
                           std::atomic<bool>& inGame, GameMonitor& gameMonitor, int32_t playerId,
                           std::shared_ptr<Queue<std::unique_ptr<GameDTO>>> sendQueue):
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
            try {
                std::unique_ptr<GameDTO> gameDTO = sendQueue->pop();
                serializer.sendGameDTO(std::move(gameDTO), wasClosed);
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
            std::unique_ptr<LobbyCommandHandler> handler =
                    LobbyCommandHandler::createHandler(std::move(command));
            std::unique_ptr<CommandDTO> commandDTO =
                    handler->execute(gameMonitor, std::ref(inGame), recvQueue);
            serializer.sendCommand(std::move(commandDTO), wasClosed);
        } catch (const std::exception& e) {
            if (wasClosed) {
                return;
            }
        }
    }
    receiver.start();
}
