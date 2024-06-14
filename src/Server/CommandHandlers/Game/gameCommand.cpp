#include "gameCommand.h"

#include "../../../Common/DTO/gameCommand.h"
#include "../../../Common/DTO/switchWeapon.h"

#include "jump.h"
#include "gameCommand.h"
#include "shoot.h"
#include "switchWeapon.h"
#include "move.h"

std::unique_ptr<GameCommandHandler> GameCommandHandler::createHandler(
        std::unique_ptr<CommandDTO> command) {
    switch (command->getCommand()) {
        case Command::MOVE: {
            auto moveCommand = dynamic_cast<GameCommandDTO*>(command.get());
            command.release();
            return std::make_unique<MoveHandler>(std::unique_ptr<GameCommandDTO>(moveCommand));
        }
        case Command::SHOOT: {
            return std::make_unique<ShootHandler>(std::unique_ptr<CommandDTO>(command.release()));
        }
        case Command::JUMP: {
            return std::make_unique<JumpHandler>(std::unique_ptr<CommandDTO>(command.release()));
        }
        case Command::SWITCH_WEAPON: {
            auto switchWeaponCommand = dynamic_cast<SwitchWeaponDTO*>(command.get());
            return std::make_unique<SwitchWeaponHandler>(
                    std::unique_ptr<SwitchWeaponDTO>(switchWeaponCommand));
        }
        default: {
            return nullptr;
        }
    }
}
