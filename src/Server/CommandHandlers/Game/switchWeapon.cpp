#include "switchWeapon.h"

SwitchWeaponHandler::SwitchWeaponHandler(std::unique_ptr<SwitchWeaponDTO> switchWeaponCommand):
        switchWeaponCommand(std::move(switchWeaponCommand)) {}

void SwitchWeaponHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning,
                                  double deltaTime) {
    std::shared_ptr<Character> character = gameMap.getCharacter(switchWeaponCommand->getPlayerId());
    if (!character) {
            std::cerr << "[SWITCH WEAPON HANDLER] Character with ID " << static_cast<int>(switchWeaponCommand->getPlayerId())
                    << " not found. Skipping move command." << std::endl;
            return;
        }

    if (!character->isAlive()) {
        std::cerr << "[SWITCH WEAPON HANDLER]  Character with ID " << static_cast<int>(switchWeaponCommand->getPlayerId())
                  << " is dead. Skipping move command." << std::endl;
        return;
    }
    else {
        std::cout << "[SWITCH WEAPON HANDLER] Switching weapon for character with ID "
                  << static_cast<int>(switchWeaponCommand->getPlayerId()) << std::endl;
         
        character->switchWeapon(switchWeaponCommand->getWeaponType());
    }
}