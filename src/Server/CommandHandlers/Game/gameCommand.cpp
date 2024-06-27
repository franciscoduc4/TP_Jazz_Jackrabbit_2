#include "gameCommand.h"

#include "../../../Common/DTO/gameCommand.h"
#include "../../../Common/DTO/switchWeapon.h"

#include "cheat.h"
#include "idle.h"
#include "jump.h"
#include "move.h"
#include "shoot.h"
#include "sprint.h"
#include "switchWeapon.h"

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
        case Command::IDLE: {
            return std::make_unique<IdleHandler>(std::unique_ptr<CommandDTO>(command.release()));
        }
        case Command::JUMP: {
            return std::make_unique<JumpHandler>(std::unique_ptr<CommandDTO>(command.release()));
        }
        case Command::SWITCH_WEAPON: {
            std::cout << "Switch weapon command received" << std::endl;
            auto switchWeaponCommand = dynamic_cast<SwitchWeaponDTO*>(command.get());
            command.release();
            return std::make_unique<SwitchWeaponHandler>(
                    std::unique_ptr<SwitchWeaponDTO>(switchWeaponCommand));
        }
        case Command::SPRINT: {
            auto sprintCommand = dynamic_cast<GameCommandDTO*>(command.get());
            command.release();
            return std::make_unique<SprintHandler>(std::unique_ptr<GameCommandDTO>(sprintCommand));
        }
        case Command::CHEAT: {
            return std::make_unique<CheatHandler>(std::unique_ptr<CommandDTO>(command.release()));
        }
        default: {
            return nullptr;
        }
    }
}
