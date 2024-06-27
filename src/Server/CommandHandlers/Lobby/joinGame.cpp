#include "joinGame.h"

#include <memory>
#include <utility>

#include "../../../Common/DTO/createGame.h"
#include "../../../Common/DTO/game.h"
#include "../../../Common/Types/gameMode.h"
#include "../../../Common/queue.h"
#include "../../Game/gameMonitor.h"

/**
 * Constructor para el manejador del comando JoinGame.
 *
 * @param command Puntero único a un JoinGameDTO que contiene los detalles del comando.
 */
JoinGameHandler::JoinGameHandler(std::unique_ptr<JoinGameDTO> command):
        command(std::move(command)) {}

/**
 * Ejecuta el comando JoinGame, permitiendo que un jugador se una a un juego existente.
 *
 * @param gameMonitor Referencia al monitor del juego para manejar el estado del juego.
 * @param inGame Estado atómico que indica si el juego está en curso.
 * @param sendQueue Cola de envío compartida para mandar datos.
 */
void JoinGameHandler::execute(GameMonitor& gameMonitor, std::atomic<bool>& inGame,
                              const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
    uint8_t playerId = command->getPlayerId();
    uint8_t gameId = command->getGameId();
    CharacterType characterType = command->getCharacterType();
    gameMonitor.joinGame(playerId, gameId, characterType, sendQueue);
}
