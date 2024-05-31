#include "jazzSpecialAttack.h"
#include "idle.h"

State* JazzSpecialAttackState::update(float time) {
    // Lógica de actualización específica para el ataque especial de Jazz
    // Volver al estado idle después de realizar el ataque especial
    return new IdleState();
}

State* JazzSpecialAttackState::shoot(Character& character, Weapon* weapon, float time) {
    // No puede disparar mientras realiza un ataque especial
    return this;
}

State* JazzSpecialAttackState::move(Character& character, std::int16_t direction, float time) {
    // Puede moverse mientras realiza un ataque especial
    character.setDir(direction);
    if (direction > 0) {
        character.moveToRight(time);
    } else {
        character.moveToLeft(time);
    }
    return this;
}

State* JazzSpecialAttackState::sprint(Character& character, float time) {
    // No puede correr más rápido de lo que ya lo hace
    return this;
}



State* JazzSpecialAttackState::reload(Weapon* weapon, float time) {
    // No puede recargar mientras realiza un ataque especial
    return this;
}

State* JazzSpecialAttackState::receiveDamage(Character& character, uint16_t dmg, float time) {
    character.recvDmg(dmg, time);
    if (character.getHealth() <= 0) {
        return new DeadState();
    }
    return this;
}

State* JazzSpecialAttackState::die(Character& character, float time) {
    character.die(time);
    return new DeadState();
}

State* JazzSpecialAttackState::revive(Character& character, float time) {
    // Lógica de reanimación
    return this;
}

State* JazzSpecialAttackState::jump(Character& character, float time) {
    // No puede saltar mientras realiza un ataque especial
    return this;
}

State* JazzSpecialAttackState::specialAttack(Character& character, float time) {
    // Ya está realizando un ataque especial
    return this;
}

State* JazzSpecialAttackState::becomeIntoxicated(Character& character, float duration) {
    // Puede intoxicarse mientras realiza un ataque especial
    return new IntoxicatedState(duration);
}

State* JazzSpecialAttackState::stopAction() {
    // Transición al estado idle
    return new IdleState();
}
