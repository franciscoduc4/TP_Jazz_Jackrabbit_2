#include "gamesList.h"

#include <map>
#include <string>
#include <utility>

/**
 * @brief Constructor de GamesListHandler.
 * 
 * @param command Comando DTO para manejar la lista de juegos.
 */
GamesListHandler::GamesListHandler(std::unique_ptr<CommandDTO> command):
        command(std::move(command)) {}

/**
 * @brief Ejecuta el handler para obtener la lista de juegos.
 * 
 * @param gameMonitor Monitor del juego para manejar las operaciones del juego.
 * @param inGame Indicador atómico que determina si el juego está en curso.
 * @param sendQueue Cola compartida para enviar DTOs.
 */
void GamesListHandler::execute(GameMonitor& gameMonitor, std::atomic<bool>& inGame,
                               const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
    gameMonitor.gamesList(sendQueue);
}
