#include "joinGame.h"

#include <memory>
#include <utility>

#include "../../Common/DTO/createGame.h"
#include "../../Common/DTO/game.h"
#include "../../Common/Types/episode.h"
#include "../../Common/Types/gameMode.h"
#include "../../Common/queue.h"
#include "../Game/gameMonitor.h"


JoinGameHandler::JoinGameHandler(std::unique_ptr<JoinGameDTO> command):
        command(std::move(command)) {}

std::unique_ptr<LobbyDTO> JoinGameHandler::execute(
        GameMonitor& gameMonitor, std::atomic<bool>& inGame,
        std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue) {
    int32_t playerId = command->getPlayerId();
    int32_t gameId = command->getGameId();
    CharacterType characterType = command->getCharacterType();
    if (gameMonitor.joinGame(playerId, gameId, characterType)) {
        return std::make_unique<LobbyDTO>(LobbyState::GAME_JOINED);
    } else {
        return std::make_unique<LobbyDTO>(LobbyState::GAME_NOT_JOINED);
    }
}