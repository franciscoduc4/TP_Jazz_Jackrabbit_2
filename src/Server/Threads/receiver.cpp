#include "receiver.h"

#include <memory>
#include <utility>

#include "../../Common/DTO/lobby.h"
#include "../CommandHandlers/Game/gameCommand.h"

ReceiverThread::ReceiverThread(std::shared_ptr<Socket> socket, std::atomic<bool>& keepPlaying,
                               std::atomic<bool>& inGame, GameMonitor& gameMonitor,
                               uint32_t playerId,
                               std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue):
        playerId(playerId),
        serializer(socket),
        deserializer(socket),
        keepPlaying(keepPlaying),
        inGame(inGame),
        wasClosed(false),
        recvQueue(recvQueue),
        gameMonitor(gameMonitor) {}

void ReceiverThread::run() {
    while (inGame) {
        try {
            std::unique_ptr<CommandDTO> commandDTO = deserializer.getCommand(wasClosed, playerId);
            recvQueue->push(std::move(commandDTO));
        } catch (const std::exception& e) {
            if (wasClosed) {
                return;
            }
        }
    }
}

