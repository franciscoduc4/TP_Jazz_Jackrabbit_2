#include "spazSpecialAttack.h"
#include "idle.h"
#include "dead.h"
#include "move.h"
#include "shooting.h"
#include "damage.h"
#include "intoxicated.h"

SpazSpecialAttackState::SpazSpecialAttackState(float time) :
    startTime(time),
    duration(2)
    {
    characterState = CharacterState::SPECIAL_ATTACK;
    }


State* SpazSpecialAttackState::update(float time) {
    // Volver al estado idle después de realizar el ataque especial
    return new IdleState();
}

State* SpazSpecialAttackState::shoot(Character& character, Weapon* weapon, float time) {
    // No puede disparar mientras realiza un ataque especial
    return new ShootingState(character, weapon, time);
}

State* SpazSpecialAttackState::move(Character& character, Move direction, float time) {
    // Puede moverse mientras realiza un ataque especial
    return new MoveState(character, direction, time);
}

State* SpazSpecialAttackState::sprint(Character& character, float time) {
    // No puede correr más rápido de lo que ya lo hace
    return nullptr;
}

State* SpazSpecialAttackState::reload(Weapon* weapon, float time) {
    // No puede recargar mientras realiza un ataque especial
    return nullptr;
}

State* SpazSpecialAttackState::receiveDamage(Character& character, uint16_t dmg, float time) {
    return new ReceivingDamageState(time);
}

State* SpazSpecialAttackState::die(Character& character, float time) {
    return new DeadState(time);
}

State* SpazSpecialAttackState::revive(Character& character, float time) {
    // Lógica de reanimación
    return nullptr;
}

State* SpazSpecialAttackState::jump(Character& character, float time) {
    // No puede saltar mientras realiza un ataque especial
    return nullptr;
}

State* SpazSpecialAttackState::specialAttack(Character& character, float time) {
    startTime = time;
    return nullptr;
}

State* SpazSpecialAttackState::becomeIntoxicated(Character& character, float duration) {
    // Puede intoxicarse mientras realiza un ataque especial
    return new IntoxicatedState(duration);
}

State* SpazSpecialAttackState::stopAction() {
    // Transición al estado idle
    return new IdleState();
}
