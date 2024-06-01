#ifndef SWITCH_WEAPON_HANDLER_H_
#define SWITCH_WEAPON_HANDLER_H_

#include "../../Common/DTO/command.h"

#include "gameCommand.h"

class SwitchWeaponHandler: public GameCommandHandler {
private:
    std::unique_ptr<CommandDTO> switchWeaponCommand;

public:
    explicit SwitchWeaponHandler(std::unique_ptr<CommandDTO> switchWeaponCommand);

    virtual void execute(Game& game, std::atomic<bool>& keepRunning, double deltaTime);
};

#endif  // SWITCH_WEAPON_HANDLER_H_