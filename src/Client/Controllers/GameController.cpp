#include "GameController.h"

#include "../Common/DTO/gameCommand.h"
#include "../Common/DTO/switchWeapon.h"
#include "../Common/DTO/specialAttack.h"
#include "../Common/DTO/cheat.h"
#include "../Common/Types/direction.h"


GameController::GameController(Serializer& serializer, Deserializer& deserializer,
                               std::shared_ptr<Queue<std::unique_ptr<DTO>>>& gameQueue):
        serializer(serializer), deserializer(deserializer), gameQueue(gameQueue) {}

void GameController::sendMsg(uint8_t playerId, Command& cmd, std::vector<uint8_t>& parameters) {
    switch (cmd) {
        case Command::IDLE:
            idle_msg(playerId);
            break;
        case Command::MOVE:
            move_msg(playerId, parameters);
            break;
        case Command::SHOOT:
            shoot_msg(playerId);
            break;
        case Command::SWITCH_WEAPON:
            switch_weapon_msg(playerId, parameters);
            break;
        case Command::SPRINT:
            sprint(playerId);
            break;
        case Command::CHEAT:
            cheat(parameters);
            break;
        case Command::SPECIAL_ATTACK:
            special_attack_msg(playerId, parameters);
            break;
    }
}

void GameController::move_msg(uint8_t playerId, std::vector<uint8_t>& parameters) {
    Direction dir = static_cast<Direction>(parameters[0]);
    std::unique_ptr<CommandDTO> move =
            std::make_unique<GameCommandDTO>(playerId, dir, Command::MOVE);
    this->serializer.sendMsg(move);
}

void GameController::shoot_msg(uint8_t playerId) {
    std::unique_ptr<CommandDTO> shoot = std::make_unique<CommandDTO>(playerId, Command::SHOOT);
    this->serializer.sendMsg(shoot);
}

void GameController::idle_msg(uint8_t playerId) {
    std::unique_ptr<CommandDTO> idle =
            std::make_unique<GameCommandDTO>(playerId, Direction::UP, Command::IDLE);
    this->serializer.sendMsg(idle);
}

void GameController::switch_weapon_msg(uint8_t playerId, std::vector<uint8_t>& parameters) {
    if (parameters.empty())
        return;
    WeaponType weaponType = static_cast<WeaponType>(parameters[0]);
    std::unique_ptr<CommandDTO> switchWeapon =
            std::make_unique<SwitchWeaponDTO>(playerId, weaponType);
    this->serializer.sendMsg(switchWeapon);
}

void GameController::sprint(uint8_t playerId) {
    std::unique_ptr<CommandDTO> sprint =
            std::make_unique<GameCommandDTO>(playerId, Command::SPRINT);
    this->serializer.sendMsg(sprint);
}

void GameController::cheat(const std::vector<uint8_t>& parameters) {
    auto cheat = static_cast<Cheat>(parameters[0]);
    std::unique_ptr<CommandDTO> cheatDto = std::make_unique<CheatDTO>(cheat);
    this->serializer.sendMsg(cheatDto);
}

void GameController::special_attack_msg(uint8_t playerId, std::vector<uint8_t>& parameters) {
    CharacterType type = static_cast<CharacterType>(parameters[0]);
    std::unique_ptr<CommandDTO> specialAttack =
            std::make_unique<SpecialAttackDTO>(playerId, type);
    this->serializer.sendMsg(specialAttack);
}

std::unique_ptr<DTO> GameController::getServerMsg() {
    std::unique_ptr<DTO> dto;
    this->gameQueue->try_pop(dto);
    return dto;
}
