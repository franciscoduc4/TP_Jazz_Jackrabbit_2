#include "startGame.h"

#include <atomic>
#include <memory>
#include <utility>

#include "../../../Common/DTO/createGame.h"
#include "../../../Common/DTO/game.h"
#include "../../../Common/Types/episode.h"
#include "../../../Common/Types/gameMode.h"
#include "../../Game/gameMonitor.h"


StartGameHandler::StartGameHandler(std::unique_ptr<StartGameDTO> command):
        command(std::move(command)) {}

std::unique_ptr<CommandDTO> StartGameHandler::execute(
        GameMonitor& gameMonitor, std::atomic<bool>& inGame,
        std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue) {
    int32_t playerId = command->getPlayerId();
    int32_t gameId = command->getGameId();
    if (gameMonitor.startGame(playerId, gameId)) {
        inGame = true;
        return std::make_unique<StartGameDTO>(playerId, gameId);
    } else {
        return nullptr;
    }
}