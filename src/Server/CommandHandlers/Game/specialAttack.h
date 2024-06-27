#ifndef SPECIAL_ATTACK_HANDLER_H
#define SPECIAL_ATTACK_HANDLER_H

#include <cstdint>
#include "../../../Common/DTO/specialAttack.h"
#include "gameCommand.h"


class SpecialAttackHandler: public GameCommandHandler {
private:
    std::unique_ptr<SpecialAttackDTO> specialAttackCommand;

public:
    explicit SpecialAttackHandler(std::unique_ptr<SpecialAttackDTO> specialAttackCommand);

    virtual void execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime);
};


#endif // SPECIAL_ATTACK_HANDLER_H

