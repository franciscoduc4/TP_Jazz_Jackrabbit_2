#include "loriSpecialAttack.h"

#include "damage.h"
#include "dead.h"
#include "idle.h"
#include "intoxicated.h"
#include "moving.h"
#include "shooting.h"

LoriSpecialAttackState::LoriSpecialAttackState(float time): startTime(time), duration(2) {
    characterState = CharacterStateEntity::SPECIAL_ATTACK;
}


std::unique_ptr<State> LoriSpecialAttackState::update(float time) {
    // Volver al estado idle después de realizar el ataque especial
    return std::unique_ptr<IdleState>();
}

std::unique_ptr<State> LoriSpecialAttackState::shoot(Character& character,
                                                     std::shared_ptr<Weapon> weapon, float time) {
    // No puede disparar mientras realiza un ataque especial
    return std::make_unique<ShootingState>(character, weapon, time);
}

std::unique_ptr<State> LoriSpecialAttackState::move(Character& character, Direction direction,
                                                    float time) {
    // Puede moverse mientras realiza un ataque especial
    return std::make_unique<MovingState>(character, direction, time);
}

std::unique_ptr<State> LoriSpecialAttackState::sprint(Character& character, float time) {
    // No puede correr más rápido de lo que ya lo hace
    return nullptr;
}

std::unique_ptr<State> LoriSpecialAttackState::reload(std::shared_ptr<Weapon> weapon, float time) {
    // No puede recargar mientras realiza un ataque especial
    return nullptr;
}

std::unique_ptr<State> LoriSpecialAttackState::receiveDamage(Character& character, uint16_t dmg,
                                                             float time) {
    return std::make_unique<ReceivingDamageState>(time);
}

std::unique_ptr<State> LoriSpecialAttackState::die(Character& character, float time) {
    return std::make_unique<DeadState>(time);
}

std::unique_ptr<State> LoriSpecialAttackState::revive(Character& character, float time) {
    // Lógica de reanimación
    return nullptr;
}

std::unique_ptr<State> LoriSpecialAttackState::jump(Character& character, float time) {
    // No puede saltar mientras realiza un ataque especial
    return nullptr;
}

std::unique_ptr<State> LoriSpecialAttackState::specialAttack(Character& character, float time) {
    startTime = time;
    return nullptr;
}

std::unique_ptr<State> LoriSpecialAttackState::becomeIntoxicated(Character& character,
                                                                 float duration) {
    // Puede intoxicarse mientras realiza un ataque especial
    return std::make_unique<IntoxicatedState>(duration);
}

std::unique_ptr<State> LoriSpecialAttackState::stopAction() {
    // Transición al estado idle
    return std::unique_ptr<IdleState>();
}
