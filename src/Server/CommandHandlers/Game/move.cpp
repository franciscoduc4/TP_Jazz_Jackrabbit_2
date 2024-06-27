#include "move.h"

MoveHandler::MoveHandler(std::unique_ptr<GameCommandDTO> moveCommand):
        moveCommand(std::move(moveCommand)) {}

/**
 * @brief Ejecuta el comando de movimiento para un personaje en el mapa del juego.
 * 
 * @param gameMap Mapa del juego donde se encuentra el personaje.
 * @param keepRunning Bandera para indicar si el juego sigue en ejecución.
 * @param deltaTime Tiempo transcurrido desde la última actualización.
 */
void MoveHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime) {
    std::shared_ptr<Character> character = gameMap.getCharacter(moveCommand->getPlayerId());
    
    if (!character || !character) {
        return;
    }
    switch (moveCommand->getMoveType()) {
        case Direction::UP:
            character->jump(deltaTime);
            break;
        case Direction::DOWN:
            character->moveDown(deltaTime);
            break;
        case Direction::LEFT:
            character->moveLeft(deltaTime);
            break;
        case Direction::RIGHT:
            character->moveRight(deltaTime);
            break;
        default:
            break;
    }
}
