#include "jumping.h"
#include "idle.h"

State* JumpingState::update(float time) {
    // Lógica de actualización específica para el estado de salto
    // Transición al estado idle si ha aterrizado
    return new IdleState();
}

State* JumpingState::shoot(Character& character, Weapon* weapon, float time) {
    // Puede disparar mientras está en el aire
    // Lógica para disparar
    return this;
}

State* JumpingState::move(Character& character, Move direction, float time) {
    // Puede moverse en el aire
    character.setDir(direction);
    if (direction > 0) {
        character.moveToRight(time);
    } else {
        character.moveToLeft(time);
    }
    return this;
}

State* JumpingState::sprint(Character& character, float time) {
    // No puede correr mientras está en el aire
    return this;
}

State* JumpingState::reload(Weapon* weapon, float time) {
    // No puede recargar mientras está en el aire
    return this;
}

State* JumpingState::receiveDamage(Character& character, uint16_t dmg, float time) {
    character.recvDmg(dmg, time);
    if (character.getHealth() <= 0) {
        return new DeadState();
    }
    return this;
}

State* JumpingState::die(Character& character, float time) {
    character.die(time);
    return new DeadState();
}

State* JumpingState::revive(Character& character, float time) {
    // Lógica de reanimación
    return this;
}

State* JumpingState::jump(Character& character, float time) {
    // Ya está en el aire, no puede saltar de nuevo
    return this;
}

State* JumpingState::specialAttack(Character& character, float time) {
    // Puede realizar un ataque especial mientras está en el aire
    return new SpecialAttackState();
}

State* JumpingState::becomeIntoxicated(Character& character, float duration) {
    // Puede intoxicarse mientras está en el aire
    return new IntoxicatedState(duration);
}

State* JumpingState::stopAction() {
    // Transición al estado idle
    return new IdleState();
}
