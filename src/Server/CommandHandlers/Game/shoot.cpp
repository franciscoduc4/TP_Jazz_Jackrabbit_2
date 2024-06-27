#include "shoot.h"

ShootHandler::ShootHandler(std::unique_ptr<CommandDTO> shootCommand):
        shootCommand(std::move(shootCommand)) {}

/**
 * @brief Ejecuta el comando de disparo para un personaje en el mapa del juego.
 * 
 * @param gameMap Mapa del juego donde se encuentra el personaje.
 * @param keepRunning Bandera para indicar si el juego sigue en ejecución.
 * @param deltaTime Tiempo transcurrido desde la última actualización.
 */
void ShootHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    std::cout << "[MANEJADOR DE DISPARO] Ejecutando comando de disparo" << std::endl;
    std::shared_ptr<Character> character = gameMap.getCharacter(shootCommand->getPlayerId());

    if (!character || !character) {
        return;
    } else {
        character->shoot(deltaTime);
    }
}
