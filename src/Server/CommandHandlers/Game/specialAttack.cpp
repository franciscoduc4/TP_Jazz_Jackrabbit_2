#include "specialAttack.h"

SpecialAttackHandler::SpecialAttackHandler(std::unique_ptr<SpecialAttackDTO> specialAttackCommand):
        specialAttackCommand(std::move(specialAttackCommand)) {}

/**
 * @brief Ejecuta el cambio de arma para un personaje en el mapa del juego.
 * 
 * @param gameMap Mapa del juego donde se encuentra el personaje.
 * @param keepRunning Bandera para indicar si el juego sigue en ejecución.
 * @param deltaTime Tiempo transcurrido desde la última actualización.
 */
void SpecialAttackHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning,
                                  double deltaTime) {
    std::shared_ptr<Character> character = gameMap.getCharacter(specialAttackCommand->getPlayerId());
    if (!character || !character) {
        return;
    }

    else {
        character->specialAttack(deltaTime);
    }
}
