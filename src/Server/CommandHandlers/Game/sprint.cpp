#include "sprint.h"

SprintHandler::SprintHandler(std::unique_ptr<GameCommandDTO> sprintCommand):
        sprintCommand(std::move(sprintCommand)) {}

/**
 * @brief Ejecuta el comando de sprint para un personaje en el mapa del juego.
 * 
 * @param gameMap Mapa del juego donde se encuentra el personaje.
 * @param keepRunning Bandera para indicar si el juego sigue en ejecución.
 * @param deltaTime Tiempo transcurrido desde la última actualización.
 */
void SprintHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    std::cout << "[MANEJADOR DE SPRINT] Ejecutando comando de sprint" << std::endl;
    std::shared_ptr<Character> character = gameMap.getCharacter(sprintCommand->getPlayerId());

    if (!character || !character) {
        return;
    }

    else {
        character->sprint(deltaTime);
    }
}
