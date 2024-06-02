#include "jazzSpecialAttack.h"
#include "idle.h"
#include "dead.h"
#include "move.h"
#include "shooting.h"
#include "damage.h"
#include "intoxicated.h"

JazzSpecialAttackState::JazzSpecialAttackState(float time) :
    startTime(time),
    duration(2)
    {
    characterState = CharacterState::SPECIAL_ATTACK;
    }


State* JazzSpecialAttackState::update(float time) {
    // Volver al estado idle después de realizar el ataque especial
    return new IdleState();
}

State* JazzSpecialAttackState::shoot(Character& character, Weapon* weapon, float time) {
    // No puede disparar mientras realiza un ataque especial
    return new ShootingState(character, weapon, time);
}

State* JazzSpecialAttackState::move(Character& character, Move direction, float time) {
    // Puede moverse mientras realiza un ataque especial
    return new MoveState(character, direction, time);
}

State* JazzSpecialAttackState::sprint(Character& character, float time) {
    // No puede correr más rápido de lo que ya lo hace
    return nullptr;
}

State* JazzSpecialAttackState::reload(Weapon* weapon, float time) {
    // No puede recargar mientras realiza un ataque especial
    return nullptr;
}

State* JazzSpecialAttackState::receiveDamage(Character& character, uint16_t dmg, float time) {
    return new ReceivingDamageState(time);
}

State* JazzSpecialAttackState::die(Character& character, float time) {
    return new DeadState(time);
}

State* JazzSpecialAttackState::revive(Character& character, float time) {
    // Lógica de reanimación
    return nullptr;
}

State* JazzSpecialAttackState::jump(Character& character, float time) {
    // No puede saltar mientras realiza un ataque especial
    return nullptr;
}

State* JazzSpecialAttackState::specialAttack(Character& character, float time) {
    startTime = time;
    return nullptr;
}

State* JazzSpecialAttackState::becomeIntoxicated(Character& character, float duration) {
    // Puede intoxicarse mientras realiza un ataque especial
    return new IntoxicatedState(duration);
}

State* JazzSpecialAttackState::stopAction() {
    // Transición al estado idle
    return new IdleState();
}
