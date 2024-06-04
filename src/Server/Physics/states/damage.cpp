#include "damage.h"

#include "../playerCharacter.h"

#include "dead.h"
#include "idle.h"
#include "intoxicated.h"
#include "jumping.h"
#include "moving.h"
#include "shooting.h"

#include "../../../Common/Config/ServerConfig.h"
#define CONFIG ServerConfig::getInstance()

ReceivingDamageState::ReceivingDamageState(float startTime):
        startTime(startTime),
        stopDamageTime(CONFIG->getDamageTime())  // CONFIG.getDamageTime();
{
    characterState = CharacterStateEntity::TAKING_DAMAGE;
}

std::unique_ptr<State> ReceivingDamageState::update(float time) {
    if (time - startTime >= stopDamageTime) {
        return std::unique_ptr<IdleState>();
    }
    return nullptr;
}

std::unique_ptr<State> ReceivingDamageState::shoot(Character& character,
                                                   std::shared_ptr<Weapon> weapon, float time) {
    if (time - startTime >= stopDamageTime) {
        return std::make_unique<ShootingState>(character, weapon, time);
    }
    return nullptr;
}

std::unique_ptr<State> ReceivingDamageState::move(Character& character, Direction direction,
                                                  float time) {
    if (time - startTime >= stopDamageTime) {
        return std::make_unique<MovingState>(character, direction, time);
    }
    return nullptr;
}

std::unique_ptr<State> ReceivingDamageState::sprint(Character& character, Direction direction,
                                                    float time) {
    if (time - startTime >= stopDamageTime) {
        return std::make_unique<MovingState>(character, direction, time);
    }
    return nullptr;
}

std::unique_ptr<State> ReceivingDamageState::reload(std::shared_ptr<Weapon> weapon, float time) {
    return std::unique_ptr<IdleState>();
}

std::unique_ptr<State> ReceivingDamageState::receiveDamage(Character& character, uint16_t damage,
                                                           float time) {
    startTime = time;
    return nullptr;
}

std::unique_ptr<State> ReceivingDamageState::die(Character& character, float respawnTime) {
    return std::make_unique<DeadState>(respawnTime);
}

std::unique_ptr<State> ReceivingDamageState::becomeIntoxicated(Character& character,
                                                               float duration) {
    return nullptr;
}

std::unique_ptr<State> ReceivingDamageState::jump(Character& character, float time) {
    return nullptr;
}

std::unique_ptr<State> ReceivingDamageState::specialAttack(Character& character, float time) {
    return nullptr;
}

std::unique_ptr<State> ReceivingDamageState::stopAction() { return nullptr; }

std::unique_ptr<State> ReceivingDamageState::revive(Character& character, float time) {
    return nullptr;
}
