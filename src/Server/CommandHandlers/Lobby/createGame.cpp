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
    uint8_t playerId = command->getPlayerId();
    uint8_t mapId = command->getMapId();
    uint8_t maxPlayers = command->getMaxPlayers();
    GameMode gameMode = command->getGameMode();
    CharacterType characterType = command->getCharacterType();
    std::string gameName = command->getGameName();

    gameMonitor.createGame(playerId, mapId, gameMode, maxPlayers, characterType, gameName,
                           recvQueue, sendQueue);
    std::cout << "[CG HANDLER] Game created" << std::endl;
}