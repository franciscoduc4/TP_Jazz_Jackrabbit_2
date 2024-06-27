#include "jump.h"

JumpHandler::JumpHandler(std::unique_ptr<CommandDTO> jumpCommand):
        moveCommand(std::move(jumpCommand)) {}

/**
 * @brief Ejecuta el comando de salto para un personaje en el mapa del juego.
 * 
 * @param gameMap Mapa del juego donde se encuentra el personaje.
 * @param keepRunning Bandera para indicar si el juego sigue en ejecución.
 * @param deltaTime Tiempo transcurrido desde la última actualización.
 */
void JumpHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    std::shared_ptr<Character> character = gameMap.getCharacter(moveCommand->getPlayerId());
    
    if (!character || !character) {
        return;
    }
    else {
        character->jump(deltaTime);
    }
}
