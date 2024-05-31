#include "sender.h"
#include <memory>
#include <utility>
#include "../CommandHandler/command.h"

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
    serializer.sendId(playerId);
    while (keepPlaying) {
        runLobby();

        while (inGame) {
            try {
                std::unique_ptr<GameDTO> gameDTO = sendQueue->pop();
                serializer.sendGameDTO(std::move(gameDTO));
            } catch (const std::exception& e) {
                if (wasClosed) {
                    return;
                }
            }
        }
    }
}

void SenderThread::runLobby() {
    while (keepPlaying && !inGame) {
        try {
            std::unique_ptr<CommandDTO> command = deserializer.getCommand(wasClosed, playerId);
            if (command == nullptr) {
                continue;
            }
            std::unique_ptr<CommandHandler> handler =
                    CommandHandler::createHandler(std::move(command));
            std::unique_ptr<LobbyDTO> lobbyDTO =
                    handler->execute(gameMonitor, std::ref(inGame), recvQueue);
            serializer.sendLobbyDTO(std::move(lobbyDTO));
        } catch (const std::exception& e) {
            if (wasClosed) {
                return;
            }
        }
    }
    receiver.start();
}
