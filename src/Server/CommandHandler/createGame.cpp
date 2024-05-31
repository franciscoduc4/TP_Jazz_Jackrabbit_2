#include "createGame.h"

#include <memory>
#include <string>
#include <utility>

#include "../../Common/DTO/createGame.h"
#include "../../Common/DTO/lobby.h"
#include "../../Common/Types/episode.h"
#include "../../Common/Types/gameMode.h"
#include "../../Common/Types/lobbyState.h"
#include "../../Common/queue.h"
#include "../Game/gameMonitor.h"


CreateGameHandler::CreateGameHandler(std::unique_ptr<CreateGameDTO> command):
        command(std::move(command)) {}

std::unique_ptr<LobbyDTO> CreateGameHandler::execute(
        GameMonitor& gameMonitor, std::atomic<bool>& inGame,
        std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue) {
    int32_t playerId = command->getPlayerId();
    Episode episode = command->getEpisodeName();
    GameMode gameMode = command->getGameMode();
    uint8_t maxPlayers = command->getMaxPlayers();
    std::string gameName = command->getGameName();
    if (gameMonitor.createGame(playerId, episode, gameMode, maxPlayers, gameName, recvQueue)) {
        return std::make_unique<LobbyDTO>(LobbyState::GAME_CREATED);
    } else {
        return std::make_unique<LobbyDTO>(LobbyState::GAME_NOT_CREATED);
    }
}