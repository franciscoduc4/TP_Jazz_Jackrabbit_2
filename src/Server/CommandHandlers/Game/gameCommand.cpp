#include "gameCommand.h"

#include "../../../Common/DTO/gameCommand.h"
#include "../../../Common/DTO/switchWeapon.h"
#include "../../../Common/DTO/specialAttack.h"

#include "cheat.h"
#include "idle.h"
#include "jump.h"
#include "move.h"
#include "shoot.h"
#include "sprint.h"
#include "specialAttack.h"
#include "switchWeapon.h"

/**
 * @brief Crea un manejador de comandos de juego basado en el tipo de comando recibido.
 * 
 * @param command Comando DTO recibido para manejar.
 * @return std::unique_ptr<GameCommandHandler> Manejador de comando de juego creado.
 */
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
            std::cout << "Comando de cambio de arma recibido" << std::endl;
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
        case Command::SPECIAL_ATTACK: {
            auto specialAttackCommand = dynamic_cast<SpecialAttackDTO*>(command.get());
            command.release();
            return std::make_unique<SpecialAttackHandler>(
                    std::unique_ptr<SpecialAttackDTO>(specialAttackCommand));
        }
        default: {
            return nullptr;
        }
    }
}
