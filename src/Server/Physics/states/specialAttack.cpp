#include "specialAttack.h"

#include "damage.h"
#include "dead.h"
#include "idle.h"
#include "intoxicated.h"
#include "moving.h"
#include "shooting.h"

SpecialAttackState::SpecialAttackState(float time): startTime(time), duration(2.0f) {
    characterState = CharacterStateEntity::SPECIAL_ATTACK;
}

std::unique_ptr<State> SpecialAttackState::update(float time) {
    // Volver al estado idle después de realizar el ataque especial
    return std::make_unique<IdleState>();
}

std::unique_ptr<State> SpecialAttackState::shoot(Character& character,
                                                 std::shared_ptr<Weapon> weapon, float time) {
    // No puede disparar mientras realiza un ataque especial
    return std::make_unique<ShootingState>(character, weapon, time);
}

std::unique_ptr<State> SpecialAttackState::move(Character& character, Direction direction,
                                                float time) {
    // Puede moverse mientras realiza un ataque especial
    return std::make_unique<MovingState>(character, direction, time);
}

std::unique_ptr<State> SpecialAttackState::sprint(Character& character, Direction direction,
                                                  float time) {
    // No puede correr más rápido de lo que ya lo hace
    return nullptr;
}

std::unique_ptr<State> SpecialAttackState::reload(std::shared_ptr<Weapon> weapon, float time) {
    // No puede recargar mientras realiza un ataque especial
    return nullptr;
}

std::unique_ptr<State> SpecialAttackState::receiveDamage(Character& character, uint16_t dmg,
                                                         float time) {
    return std::make_unique<ReceivingDamageState>(time);
}

std::unique_ptr<State> SpecialAttackState::die(Character& character, float time) {
    return std::make_unique<DeadState>(time);
}

std::unique_ptr<State> SpecialAttackState::revive(Character& character, float time) {
    // Lógica de reanimación
    return nullptr;
}

std::unique_ptr<State> SpecialAttackState::jump(Character& character, float time) {
    // No puede saltar mientras realiza un ataque especial
    return nullptr;
}

std::unique_ptr<State> SpecialAttackState::specialAttack(Character& character, float time) {
    startTime = time;
    return nullptr;
}

std::unique_ptr<State> SpecialAttackState::becomeIntoxicated(Character& character, float duration) {
    // Puede intoxicarse mientras realiza un ataque especial
    return std::make_unique<IntoxicatedState>(duration);
}

std::unique_ptr<State> SpecialAttackState::stopAction() {
    // Transición al estado idle
    return std::make_unique<IdleState>();
}
