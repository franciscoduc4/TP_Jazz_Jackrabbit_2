#include "specialAttack.h"

#include "damage.h"
#include "dead.h"
#include "idle.h"
#include "intoxicated.h"
#include "moving.h"
#include "shooting.h"
#include "sprinting.h"

SpecialAttackState::SpecialAttackState(Character& character, float time):
        startTime(time), duration(2.0f), character(character) {
    characterState = CharacterStateEntity::SPECIAL_ATTACK;
}

std::unique_ptr<State> SpecialAttackState::exec(float time) {
    // Volver al estado idle después de realizar el ataque especial
    if (duration <= 0.0) {
        duration = 2.0f;
        return std::make_unique<IdleState>(character);
    }
    duration -= 0.2;
    character.specialAttack();
    return nullptr;
    //character.specialAttack();
    //return std::make_unique<IdleState>(character);
}

std::unique_ptr<State> SpecialAttackState::shoot(const std::shared_ptr<Weapon>& weapon,
                                                 float time) {
    // No puede disparar mientras realiza un ataque especial
    return nullptr;
}

std::unique_ptr<State> SpecialAttackState::move(Direction direction, float time) {
    // No puede moverse mientras realiza un ataque especial
    return nullptr;
}

std::unique_ptr<State> SpecialAttackState::sprint(Direction direction, float time) {
    // No puede correr más rápido de lo que ya lo hace
    return nullptr;
}


std::unique_ptr<State> SpecialAttackState::receiveDamage(uint8_t dmg, float time) {
    return std::make_unique<ReceivingDamageState>(character, time, dmg);
}

std::unique_ptr<State> SpecialAttackState::die(float time) {
    return std::make_unique<DeadState>(character, time);
}

std::unique_ptr<State> SpecialAttackState::revive(float time) {
    // Lógica de reanimación
    return nullptr;
}

std::unique_ptr<State> SpecialAttackState::jump(float time) {
    // No puede saltar mientras realiza un ataque especial
    return nullptr;
}

std::unique_ptr<State> SpecialAttackState::specialAttack(float time) {
    startTime = time;
    return nullptr;
}

std::unique_ptr<State> SpecialAttackState::becomeIntoxicated(float period) {
    return nullptr;
}

std::unique_ptr<State> SpecialAttackState::stopAction() {
    // Transición al estado idle
    return std::make_unique<IdleState>(character);
}
