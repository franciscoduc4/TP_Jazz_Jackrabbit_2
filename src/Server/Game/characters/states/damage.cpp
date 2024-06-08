#include "damage.h"

#include "../../../../Common/Config/ServerConfig.h"
#include "../character.h"

#include "dead.h"
#include "idle.h"
#include "intoxicated.h"
#include "jumping.h"
#include "moving.h"
#include "shooting.h"
#include "specialAttack.h"

#define CONFIG ServerConfig::getInstance()

ReceivingDamageState::ReceivingDamageState(float startTime):
        startTime(startTime), timeReceivingDamage(CONFIG->getCharacterDamageTime()) {
    characterState = CharacterStateEntity::TAKING_DAMAGE;
}

std::unique_ptr<State> ReceivingDamageState::exec(Character& character, float time) {
    if (isReceivingDamage(time)) {
        return nullptr;
    }
    return std::unique_ptr<IdleState>();
}

std::unique_ptr<State> ReceivingDamageState::shoot(Character& character,
                                                   std::shared_ptr<Weapon> weapon, float time) {
    if (isReceivingDamage(time)) {
        return nullptr;
    }
    return std::make_unique<ShootingState>(character, weapon, time);
}

std::unique_ptr<State> ReceivingDamageState::move(Character& character, Direction direction,
                                                  float time) {
    if (isReceivingDamage(time)) {
        return nullptr;
    }
    return std::make_unique<MovingState>(character, direction, time);
}

std::unique_ptr<State> ReceivingDamageState::sprint(Character& character, Direction direction,
                                                    float time) {
    if (isReceivingDamage(time)) {
        return nullptr;
    }
    return std::make_unique<MovingState>(character, direction, time);
}

std::unique_ptr<State> ReceivingDamageState::receiveDamage(Character& character, uint16_t dmg,
                                                           float time) {
    damage = dmg;
    startTime = time;
    return nullptr;
}

std::unique_ptr<State> ReceivingDamageState::die(Character& character, float respawnTime) {
    return std::make_unique<DeadState>(respawnTime);
}

std::unique_ptr<State> ReceivingDamageState::becomeIntoxicated(Character& character,
                                                               float duration) {
    if (isReceivingDamage(duration)) {
        return nullptr;
    }
    return std::make_unique<IntoxicatedState>(duration);
}

std::unique_ptr<State> ReceivingDamageState::jump(Character& character, float time) {
    if (isReceivingDamage(time)) {
        return nullptr;
    }
    return std::make_unique<JumpingState>();
}

std::unique_ptr<State> ReceivingDamageState::specialAttack(Character& character, float time) {
    if (isReceivingDamage(time)) {
        return nullptr;
    }
    return std::make_unique<SpecialAttackState>(time);
}

std::unique_ptr<State> ReceivingDamageState::stopAction() { return nullptr; }

std::unique_ptr<State> ReceivingDamageState::revive(Character& character, float time) {
    return nullptr;
}

bool ReceivingDamageState::isReceivingDamage(float time) {
    return (time - startTime) < timeReceivingDamage;
}
