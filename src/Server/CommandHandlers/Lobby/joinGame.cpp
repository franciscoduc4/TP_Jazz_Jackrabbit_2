#include "joinGame.h"

#include <memory>
#include <utility>

#include "../../../Common/DTO/createGame.h"
#include "../../../Common/DTO/game.h"
#include "../../../Common/Types/episode.h"
#include "../../../Common/Types/gameMode.h"
#include "../../../Common/queue.h"
#include "../../Game/gameMonitor.h"


JoinGameHandler::JoinGameHandler(std::unique_ptr<JoinGameDTO> command):
        command(std::move(command)) {}

std::unique_ptr<CommandDTO> JoinGameHandler::execute(
        GameMonitor& gameMonitor, std::atomic<bool>& inGame,
        std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
        std::shared_ptr<Queue<std::unique_ptr<GameDTO>>> sendQueue) {
    uint32_t playerId = command->getPlayerId();
    uint32_t gameId = command->getGameId();
    CharacterType characterType = command->getCharacterType();
    uint8_t currentPlayers = gameMonitor.getCurrentPlayers(gameId);
    if (gameMonitor.joinGame(playerId, gameId, characterType, sendQueue)) {
        return std::make_unique<JoinGameDTO>(playerId, gameId, currentPlayers);
    } else {
        return nullptr;
    }
}