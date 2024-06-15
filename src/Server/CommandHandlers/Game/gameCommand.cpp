#include "gameCommand.h"

#include "../../../Common/DTO/gameCommand.h"
#include "../../../Common/DTO/switchWeapon.h"

#include "idle.h"
#include "jump.h"
#include "move.h"
#include "shoot.h"
#include "switchWeapon.h"

std::unique_ptr<GameCommandHandler> GameCommandHandler::createHandler(
        std::unique_ptr<CommandDTO> command) {
    switch (command->getCommand()) {
        case Command::MOVE: {
            auto moveCommand = dynamic_cast<GameCommandDTO*>(command.get());
            command.release();
            std::cout << "[GAME CH] Creating move handler" << std::endl;
            return std::make_unique<MoveHandler>(std::unique_ptr<GameCommandDTO>(moveCommand));
        }
        case Command::SHOOT: {
            std::cout << "[GAME CH] Creating shoot handler" << std::endl;
            return std::make_unique<ShootHandler>(std::unique_ptr<CommandDTO>(command.release()));
        }
        case Command::JUMP: {
            std::cout << "[GAME CH] Creating jump handler" << std::endl;
            return std::make_unique<JumpHandler>(std::unique_ptr<CommandDTO>(command.release()));
        }
        case Command::IDLE: {
            std::cout << "[GAME CH] Creating idle handler" << std::endl;
            return std::make_unique<IdleHandler>(std::unique_ptr<CommandDTO>(command.release()));
        }
        case Command::SWITCH_WEAPON: {
            auto switchWeaponCommand = dynamic_cast<SwitchWeaponDTO*>(command.get());
            command.release();
            std::cout << "[GAME CH] Creating switch weapon handler" << std::endl;
            return std::make_unique<SwitchWeaponHandler>(
                    std::unique_ptr<SwitchWeaponDTO>(switchWeaponCommand));
        }
        default: {
            std::cout << "[GAME CH] Unknown command received" << std::endl;
            return nullptr;
        }
    }
}
