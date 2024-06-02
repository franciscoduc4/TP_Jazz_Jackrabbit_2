#include "loriSpecialAttack.h"
#include "idle.h"
#include "dead.h"
#include "move.h"
#include "shooting.h"
#include "damage.h"
#include "intoxicated.h"

LoriSpecialAttackState::LoriSpecialAttackState(float time):
    startTime(startTime),
    duration(2)
    {
    characterState = CharacterState::SPECIAL_ATTACK;
    }


State* LoriSpecialAttackState::update(float time) {
    // Volver al estado idle después de realizar el ataque especial
    return new IdleState();
}

State* LoriSpecialAttackState::shoot(Character& character, Weapon* weapon, float time) {
    // No puede disparar mientras realiza un ataque especial
    return new ShootingState(character, weapon, time);
}

State* LoriSpecialAttackState::move(Character& character, Move direction, float time) {
    // Puede moverse mientras realiza un ataque especial
    return new MoveState(character, direction, time);
}

State* LoriSpecialAttackState::sprint(Character& character, float time) {
    // No puede correr más rápido de lo que ya lo hace
    return nullptr;
}

State* LoriSpecialAttackState::reload(Weapon* weapon, float time) {
    // No puede recargar mientras realiza un ataque especial
    return nullptr;
}

State* LoriSpecialAttackState::receiveDamage(Character& character, uint16_t dmg, float time) {
    return new ReceivingDamageState(time);
}

State* LoriSpecialAttackState::die(Character& character, float time) {
    return new DeadState(time);
}

State* LoriSpecialAttackState::revive(Character& character, float time) {
    // Lógica de reanimación
    return nullptr;
}

State* LoriSpecialAttackState::jump(Character& character, float time) {
    // No puede saltar mientras realiza un ataque especial
    return nullptr;
}

State* LoriSpecialAttackState::specialAttack(Character& character, float time) {
    startTime = time;
    return nullptr;
}

State* LoriSpecialAttackState::becomeIntoxicated(Character& character, float duration) {
    // Puede intoxicarse mientras realiza un ataque especial
    return new IntoxicatedState(duration);
}

State* LoriSpecialAttackState::stopAction() {
    // Transición al estado idle
    return new IdleState();
}
