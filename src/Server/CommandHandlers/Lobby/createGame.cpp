#include "createGame.h"

#include <memory>
#include <string>
#include <utility>

#include "../../../Common/DTO/createGame.h"
#include "../../../Common/DTO/lobby.h"
#include "../../../Common/Types/gameMode.h"
#include "../../../Common/Types/lobbyState.h"
#include "../../../Common/queue.h"
#include "../../Game/gameMonitor.h"


CreateGameHandler::CreateGameHandler(std::unique_ptr<CreateGameDTO> command):
        command(std::move(command)) {}

void CreateGameHandler::execute(GameMonitor& gameMonitor, std::atomic<bool>& inGame,
                                std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                                std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    uint32_t playerId = command->getPlayerId();
    uint32_t episodeId = command->getEpisodeId();
    std::string episodeName = command->getEpisodeName();
    uint8_t maxPlayers = command->getMaxPlayers();
    GameMode gameMode = (maxPlayers == 1) ? GameMode::SINGLE_PLAYER : GameMode::PARTY_MODE;
    CharacterType characterType = command->getCharacterType();
    std::string gameName = command->getGameName();
    uint32_t gameId = gameMonitor.getGamesList().size();

    gameMonitor.createGame(playerId, episodeId, episodeName, gameMode, maxPlayers, characterType,
                           gameName, recvQueue, gameId, sendQueue);
}