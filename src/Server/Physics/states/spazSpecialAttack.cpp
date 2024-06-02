#include "spazSpecialAttack.h"
#include "idle.h"
#include "dead.h"
#include "move.h"
#include "shooting.h"
#include "damage.h"
#include "intoxicated.h"

SpazSpecialAttackState::SpazSpecialAttackState(float time) :
    startTime(time),
    duration(2.0f)
{
    characterState = CharacterStateEntity::SPECIAL_ATTACK;
}

std::unique_ptr<State> SpazSpecialAttackState::update(float time) {
    // Volver al estado idle después de realizar el ataque especial
    return std::make_unique<IdleState>();
}

std::unique_ptr<State> SpazSpecialAttackState::shoot
(Character& character, std::unique_ptr<Weapon> weapon, float time) {
    // No puede disparar mientras realiza un ataque especial
    return std::make_unique<ShootingState>(character, weapon, time);
}

std::unique_ptr<State> SpazSpecialAttackState::move
(Character& character, Move direction, float time) {
    // Puede moverse mientras realiza un ataque especial
    return std::make_unique<MoveState>(character, direction, time);
}

std::unique_ptr<State> SpazSpecialAttackState::sprint(Character& character, float time) {
    // No puede correr más rápido de lo que ya lo hace
    return nullptr;
}

std::unique_ptr<State> SpazSpecialAttackState::reload(std::unique_ptr<Weapon> weapon, float time) {
    // No puede recargar mientras realiza un ataque especial
    return nullptr;
}

std::unique_ptr<State> SpazSpecialAttackState::receiveDamage
(Character& character, uint16_t dmg, float time) {
    return std::make_unique<ReceivingDamageState>(time);
}

std::unique_ptr<State> SpazSpecialAttackState::die(Character& character, float time) {
    return std::make_unique<DeadState>(time);
}

std::unique_ptr<State> SpazSpecialAttackState::revive(Character& character, float time) {
    // Lógica de reanimación
    return nullptr;
}

std::unique_ptr<State> SpazSpecialAttackState::jump(Character& character, float time) {
    // No puede saltar mientras realiza un ataque especial
    return nullptr;
}

std::unique_ptr<State> SpazSpecialAttackState::specialAttack(Character& character, float time) {
    startTime = time;
    return nullptr;
}

std::unique_ptr<State> SpazSpecialAttackState::becomeIntoxicated
(Character& character, float duration) {
    // Puede intoxicarse mientras realiza un ataque especial
    return std::make_unique<IntoxicatedState>(duration);
}

std::unique_ptr<State> SpazSpecialAttackState::stopAction() {
    // Transición al estado idle
    return std::make_unique<IdleState>();
}
