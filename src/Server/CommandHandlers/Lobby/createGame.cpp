#include "createGame.h"

#include <memory>
#include <string>
#include <utility>

#include "../../../Common/DTO/createGame.h"
#include "../../../Common/DTO/lobby.h"
#include "../../../Common/Types/episode.h"
#include "../../../Common/Types/gameMode.h"
#include "../../../Common/Types/lobbyState.h"
#include "../../../Common/queue.h"
#include "../../Game/gameMonitor.h"


CreateGameHandler::CreateGameHandler(std::unique_ptr<CreateGameDTO> command):
        command(std::move(command)) {}

std::unique_ptr<CommandDTO> CreateGameHandler::execute(
        GameMonitor& gameMonitor, std::atomic<bool>& inGame,
        std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue) {
    int32_t playerId = 0;
    Episode episode = command->getEpisodeName();
    uint8_t maxPlayers = command->getMaxPlayers();
    GameMode gameMode = (maxPlayers == 1) ? GameMode::SINGLE_PLAYER : GameMode::PARTY_MODE;
    CharacterType characterType = command->getCharacterType();
    std::string gameName = command->getGameName();
    int32_t gameId = gameMonitor.getGamesList().size();
    if (gameMonitor.createGame(playerId, episode, gameMode, maxPlayers, characterType, gameName,
                               recvQueue, gameId)) {
        return std::make_unique<CreateGameDTO>(playerId, episode, maxPlayers,
                                               characterType, gameName, gameId);
    } else {
        return nullptr;
    }
}