#include "switchWeapon.h"

SwitchWeaponHandler::SwitchWeaponHandler(std::unique_ptr<SwitchWeaponDTO> switchWeaponCommand):
        switchWeaponCommand(std::move(switchWeaponCommand)) {}

void SwitchWeaponHandler::execute(Game& game, std::atomic<bool>& keepRunning, double deltaTime) {
    std::shared_ptr<Character> character = game.getCharacter(switchWeaponCommand->getPlayerId());
    character->switchWeapon(switchWeaponCommand->getWeaponType());
}