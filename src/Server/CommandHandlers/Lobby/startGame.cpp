#include "startGame.h"

#include <atomic>
#include <memory>
#include <utility>

#include "../../../Common/DTO/createGame.h"
#include "../../../Common/DTO/game.h"
#include "../../../Common/Types/gameMode.h"
#include "../../Game/gameMonitor.h"


StartGameHandler::StartGameHandler(std::unique_ptr<StartGameDTO> command):
        command(std::move(command)) {}

std::unique_ptr<CommandDTO> StartGameHandler::execute(
        GameMonitor& gameMonitor, std::atomic<bool>& inGame,
        std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
        std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    uint32_t playerId = command->getPlayerId();
    uint32_t gameId = command->getGameId();
    gameMonitor.startGame(playerId, gameId);
    inGame = true;
}