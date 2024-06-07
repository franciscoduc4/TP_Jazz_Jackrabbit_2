#ifndef SWITCH_WEAPON_HANDLER_H_
#define SWITCH_WEAPON_HANDLER_H_

#include "../../../Common/DTO/switchWeapon.h"

#include "gameCommand.h"

class SwitchWeaponHandler: public GameCommandHandler {
private:
    std::unique_ptr<SwitchWeaponDTO> switchWeaponCommand;

public:
    explicit SwitchWeaponHandler(std::unique_ptr<SwitchWeaponDTO> switchWeaponCommand);

    virtual void execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime);
};

#endif  // SWITCH_WEAPON_HANDLER_H_
