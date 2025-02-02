#include "dead.h"

#include "idle.h"

DeadState::DeadState(Character& character, float deathTime):
        startTime(deathTime),
        reviveTime(ServerConfig::getCharacterReviveTime()),
        character(character) {
    characterState = CharacterStateEntity::DEAD;
}

std::unique_ptr<State> DeadState::exec(float time) { return nullptr; }

std::unique_ptr<State> DeadState::shoot(const std::shared_ptr<Weapon>& weapon, float time) {
    return nullptr;
}

std::unique_ptr<State> DeadState::move(Direction direction, float time) { return nullptr; }

std::unique_ptr<State> DeadState::sprint(Direction direction, float time) { return nullptr; }


std::unique_ptr<State> DeadState::receiveDamage(uint8_t dmg, float time) { return nullptr; }

std::unique_ptr<State> DeadState::die(float time) { return nullptr; }

std::unique_ptr<State> DeadState::revive(float time) {
    currentTime += time;
    if (canRevive(time)) {
        std::cout << "[DEAD STATE] Reviving character" << std::endl;
        return std::make_unique<IdleState>(character);
    }
    return nullptr;
}

std::unique_ptr<State> DeadState::jump(float time) { return nullptr; }

std::unique_ptr<State> DeadState::specialAttack(float time) { return nullptr; }

std::unique_ptr<State> DeadState::becomeIntoxicated(float duration) { return nullptr; }

std::unique_ptr<State> DeadState::stopAction() { return nullptr; }

bool DeadState::canRevive(float time) const {
    std::cout << "[DEAD STATE] currentTime: " << currentTime << " startTime: " << startTime
              << " reviveTime: " << reviveTime << std::endl;
    return (currentTime - startTime) > reviveTime;
}