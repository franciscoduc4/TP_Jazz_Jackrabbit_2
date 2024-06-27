#include "startGame.h"

#include <atomic>
#include <memory>
#include <utility>

/**
 * Constructor para el manejador del comando StartGame.
 *
 * @param command Puntero único a un StartGameDTO que contiene los detalles del comando.
 */
StartGameHandler::StartGameHandler(std::unique_ptr<StartGameDTO> command):
        command(std::move(command)) {}

/**
 * Ejecuta el comando StartGame, iniciando el juego en el monitor del juego.
 *
 * @param gameMonitor Referencia al monitor del juego para manejar el estado del juego.
 * @param inGame Estado atómico que indica si el juego está en curso.
 * @param sendQueue Cola de envío compartida para mandar datos.
 */
void StartGameHandler::execute(GameMonitor& gameMonitor, std::atomic<bool>& inGame,
                               const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
    uint8_t playerId = command->getPlayerId();
    uint8_t gameId = command->getGameId();
    gameMonitor.startGame(playerId, gameId, sendQueue);
    std::cout << "[SG HANDLER] Game started" << std::endl;
}
