#include "joinGame.h"

#include <memory>
#include <utility>

#include "../../../Common/DTO/createGame.h"
#include "../../../Common/DTO/game.h"
#include "../../../Common/Types/gameMode.h"
#include "../../../Common/queue.h"
#include "../../Game/gameMonitor.h"


JoinGameHandler::JoinGameHandler(std::unique_ptr<JoinGameDTO> command):
        command(std::move(command)) {}

void JoinGameHandler::execute(GameMonitor& gameMonitor, std::atomic<bool>& inGame,
                              std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    uint8_t playerId = command->getPlayerId();
    uint8_t gameId = command->getGameId();
    CharacterType characterType = command->getCharacterType();
    gameMonitor.joinGame(playerId, gameId, characterType, sendQueue);
}