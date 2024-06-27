#include "switchWeapon.h"

SwitchWeaponHandler::SwitchWeaponHandler(std::unique_ptr<SwitchWeaponDTO> switchWeaponCommand):
        switchWeaponCommand(std::move(switchWeaponCommand)) {}

/**
 * @brief Ejecuta el cambio de arma para un personaje en el mapa del juego.
 * 
 * @param gameMap Mapa del juego donde se encuentra el personaje.
 * @param keepRunning Bandera para indicar si el juego sigue en ejecución.
 * @param deltaTime Tiempo transcurrido desde la última actualización.
 */
void SwitchWeaponHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning,
                                  double deltaTime) {
    std::shared_ptr<Character> character = gameMap.getCharacter(switchWeaponCommand->getPlayerId());
    if (!character || !character) {
        return;
    }

    else {
        character->switchWeapon(switchWeaponCommand->getWeaponType());
    }
}
