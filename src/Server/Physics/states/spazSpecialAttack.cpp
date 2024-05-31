#include "spazSpecialAttack.h"
#include "idle.h"

State* SpazSpecialAttackState::update(float time) {
    // Lógica de actualización específica para el ataque especial de Spaz
    // Volver al estado idle después de realizar el ataque especial
    return new IdleState();
}

State* SpazSpecialAttackState::shoot(Character& character, Weapon* weapon, float time) {
    // No puede disparar mientras realiza un ataque especial
    return this;
}

State* SpazSpecialAttackState::move(Character& character, std::int16_t direction, float time) {
    // Puede moverse mientras realiza un ataque especial
    character.setDir(direction);
    if (direction > 0) {
        character.moveToRight(time);
    } else {
        character.moveToLeft(time);
    }
    return this;
}

State* SpazSpecialAttackState::sprint(Character& character, float time) {
    // No puede correr más rápido de lo que ya lo hace
    return this;
}

State* SpazSpecialAttackState::reload(Weapon* weapon, float time) {
    // No puede recargar mientras realiza un ataque especial
    return this;
}

State* SpazSpecialAttackState::receiveDamage(Character& character, uint16_t dmg, float time) {
    character.recvDmg(dmg, time);
    if (character.getHealth() <= 0) {
        return new DeadState();
    }
    return this;
}

State* SpazSpecialAttackState::die(Character& character, float time) {
    character.die(time);
    return new DeadState();
}

State* SpazSpecialAttackState::revive(Character& character, float time) {
    // Lógica de reanimación
    return this;
}

State* SpazSpecialAttackState::jump(Character& character, float time) {
    // No puede saltar mientras realiza un ataque especial
    return this;
}

State* SpazSpecialAttackState::specialAttack(Character& character, float time) {
    // Ya está realizando un ataque especial
    return this;
}

State* SpazSpecialAttackState::becomeIntoxicated(Character& character, float duration) {
    // Puede intoxicarse mientras realiza un ataque especial
    return new IntoxicatedState(duration);
}

State* SpazSpecialAttackState::stopAction() {
    // Transición al estado idle
    return new IdleState();
}
