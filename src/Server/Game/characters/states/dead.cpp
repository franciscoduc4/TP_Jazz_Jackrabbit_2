#include "dead.h"

#include <utility>

#include "../../../../Common/Config/ServerConfig.h"

#include "idle.h"
#define CONFIG ServerConfig::getInstance()

DeadState::DeadState(float deathTime):
        startTime(deathTime), reviveTime(CONFIG->getCharacterReviveTime()) {
    characterState = CharacterStateEntity::DEAD;
}

std::unique_ptr<State> DeadState::exec(Character& character, float time) { return nullptr; }

std::unique_ptr<State> DeadState::shoot(Character& character, std::shared_ptr<Weapon> weapon,
                                        float time) {
    return nullptr;
}

std::unique_ptr<State> DeadState::move(Character& character, Direction direction, float time) {
    return nullptr;
}

std::unique_ptr<State> DeadState::sprint(Character& character, Direction direction, float time) {
    return nullptr;
}


std::unique_ptr<State> DeadState::receiveDamage(Character& character, uint16_t dmg, float time) {
    return nullptr;
}

std::unique_ptr<State> DeadState::die(Character& character, float time) { return nullptr; }

std::unique_ptr<State> DeadState::revive(Character& character, float time) {
    if (canRevive(time)) {
        return std::unique_ptr<IdleState>();
    }
    return nullptr;
}

std::unique_ptr<State> DeadState::jump(Character& character, float time) { return nullptr; }

std::unique_ptr<State> DeadState::specialAttack(Character& character, float time) {
    return nullptr;
}

std::unique_ptr<State> DeadState::becomeIntoxicated(Character& character, float duration) {
    return nullptr;
}

std::unique_ptr<State> DeadState::stopAction() { return nullptr; }

bool DeadState::canRevive(float time) { return (time - startTime) > reviveTime; }