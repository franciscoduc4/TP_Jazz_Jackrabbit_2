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

/**
 * @brief Constructor de CreateGameHandler.
 * 
 * @param command Comando DTO para crear el juego.
 */
CreateGameHandler::CreateGameHandler(std::unique_ptr<CreateGameDTO> command):
        command(std::move(command)) {}

/**
 * @brief Ejecuta el handler para crear un nuevo juego.
 * 
 * @param gameMonitor Monitor del juego para manejar las operaciones del juego.
 * @param inGame Indicador atómico que determina si el juego está en curso.
 * @param sendQueue Cola compartida para enviar DTOs.
 */
void CreateGameHandler::execute(GameMonitor& gameMonitor, std::atomic<bool>& inGame,
                                const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
    uint8_t playerId = command->getPlayerId();
    uint8_t mapId = command->getMapId();
    uint8_t maxPlayers = command->getMaxPlayers();
    GameMode gameMode = command->getGameMode();
    CharacterType characterType = command->getCharacterType();
    std::string gameName = command->getGameName();

    gameMonitor.createGame(playerId, mapId, gameMode, maxPlayers, characterType, gameName, sendQueue);
    std::cout << "[CG HANDLER] Juego creado" << std::endl;
}
