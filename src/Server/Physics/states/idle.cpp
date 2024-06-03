#include "idle.h"

#include "../playerCharacter.h"

#include "dead.h"
#include "intoxicated.h"
#include "jumping.h"
#include "moving.h"
#include "shooting.h"

IdleState::IdleState() { characterState = IDLE; }

std::unique_ptr<State> IdleState::update(float time) { return nullptr; }

std::unique_ptr<State> IdleState::shoot(Character& character, std::shared_ptr<Weapon> weapon,
                                        float time) {
    if (weapon->isEmpty() || !weapon->shootTime(time)) {
        return nullptr;
    }
    return std::make_unique<ShootingState>(character, weapon, time);
}

std::unique_ptr<State> IdleState::move(Character& character, Direction direction, float time) {
    return std::make_unique<MovingState>(character, direction, time);
}

// std::unique_ptr<State> IdleState::sprint(Character& character, float time) {
//     character.sprint(time);
//     return std::unique_ptr<MovingState>(character, direction, time)(character.getDir());
// }

std::unique_ptr<State> IdleState::reload(std::shared_ptr<Weapon> weapon, float time) {

    return nullptr;
}

std::unique_ptr<State> IdleState::receiveDamage(Character& character, uint16_t dmg, float time) {
    character.recvDamage(dmg, time);
    if (character.getHealth() <= 0) {
        return std::make_unique<DeadState>(time);
    }
    return nullptr;
}

std::unique_ptr<State> IdleState::die(Character& character, float time) {
    character.die(time);
    return std::make_unique<DeadState>(time);
}

std::unique_ptr<State> IdleState::revive(Character& character, float time) { return nullptr; }

// std::unique_ptr<State> IdleState::jump(Character& character, float time) {
//     character.jump(time);
//     return std::unique_ptr<JumpingState>();
// }

// std::unique_ptr<State> IdleState::specialAttack(Character& character, float time) {
//     return new SpecialAttackState();
// }

std::unique_ptr<State> IdleState::becomeIntoxicated(Character& character, float duration) {
    return std::make_unique<IntoxicatedState>(duration);
}

std::unique_ptr<State> IdleState::stopAction() { return nullptr; }
