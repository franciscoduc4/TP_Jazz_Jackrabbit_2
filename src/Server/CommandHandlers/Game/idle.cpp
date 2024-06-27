#include "idle.h"

IdleHandler::IdleHandler(std::unique_ptr<CommandDTO> idleCommand): 
    idleCommand(std::move(idleCommand)) {}

/**
 * @brief Ejecuta el comando de inactividad para un personaje en el mapa del juego.
 * 
 * @param gameMap Mapa del juego donde se encuentra el personaje.
 * @param keepRunning Bandera para indicar si el juego sigue en ejecución.
 * @param deltaTime Tiempo transcurrido desde la última actualización.
 */
void IdleHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    std::shared_ptr<Character> character = gameMap.getCharacter(idleCommand->getPlayerId());

    if (!character || !character) {
        return;
    } 
    else {
        character->idle(deltaTime);
    }
    std::cout << "[MANEJADOR DE INACTIVIDAD] Comando de inactividad ejecutado" << std::endl;    
}
