#include "switchWeapon.h"

SwitchWeaponHandler::SwitchWeaponHandler(std::unique_ptr<SwitchWeaponDTO> switchWeaponCommand):
        switchWeaponCommand(std::move(switchWeaponCommand)) {}

void SwitchWeaponHandler::execute(GameMap& gameMap, std::atomic<bool>& keepRunning,
                                  double deltaTime) {
    std::shared_ptr<Character> character = gameMap.getCharacter(switchWeaponCommand->getPlayerId());
    character->switchWeapon(switchWeaponCommand->getWeaponType());
}