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
#include "sprinting.h"

ReceivingDamageState::ReceivingDamageState(Character& character, float startTime, uint8_t damage):
        character(character) {
    characterState = CharacterStateEntity::TAKING_DAMAGE;
}

std::unique_ptr<State> ReceivingDamageState::exec(float time) {
    return receiveDamage(damage, time);
}

std::unique_ptr<State> ReceivingDamageState::shoot(const std::shared_ptr<Weapon>& weapon,
                                                   float time) {
    return std::make_unique<ShootingState>(character, weapon, time);
}

std::unique_ptr<State> ReceivingDamageState::move(Direction direction, float time) {
    return std::make_unique<MovingState>(character, direction);
}

std::unique_ptr<State> ReceivingDamageState::sprint(Direction direction, float time) {
    return std::make_unique<SprintingState>(character, direction);
}

std::unique_ptr<State> ReceivingDamageState::receiveDamage(uint8_t dmg, float time) {
    std::cout << "[RECEIVING DAMAGE] Receiving damage" << std::endl;
    character.recvDamage(dmg);
    if (!character.isAlive()) {
        return die(time);
    }
    return nullptr;
}

std::unique_ptr<State> ReceivingDamageState::die(float respawnTime) {
    return std::make_unique<DeadState>(character, respawnTime);
}

std::unique_ptr<State> ReceivingDamageState::becomeIntoxicated(float duration) {
    return std::make_unique<IntoxicatedState>(character, duration);
}

std::unique_ptr<State> ReceivingDamageState::jump(float time) {
    return std::make_unique<JumpingState>(character);
}

std::unique_ptr<State> ReceivingDamageState::specialAttack(float time) {
    return std::make_unique<SpecialAttackState>(character, time);
}

std::unique_ptr<State> ReceivingDamageState::stopAction() { return nullptr; }

std::unique_ptr<State> ReceivingDamageState::revive(float time) { return nullptr; }
