#include "running.h"
#include "idle_state.h"

State* RunningState::update(float time) {
    // Lógica de actualización específica para el estado de correr
    return this;
}

State* RunningState::shoot(Character& character, Weapon* weapon, float time) {
    // Puede disparar mientras corre
    return new ShootingState();
}

State* RunningState::move(Character& character, Move direction, float time) {
    // Continuar corriendo en la misma dirección
    character.setDir(direction);
    if (direction > 0) {
        character.moveToRight(time);
    } else {
        character.moveToLeft(time);
    }
    return this;
}

State* RunningState::sprint(Character& character, float time) {
    // No puede correr más rápido de lo que ya lo hace
    return this;
}


State* RunningState::reload(Weapon* weapon, float time) {
    // No puede recargar mientras corre
    return this;
}

State* RunningState::receiveDamage(Character& character, uint16_t dmg, float time) {
    character.recvDmg(dmg, time);
    if (character.getHealth() <= 0) {
        return new DeadState();
    }
    return this;
}

State* RunningState::die(Character& character, float time) {
    character.die(time);
    return new DeadState();
}

State* RunningState::revive(Character& character, float time) {
    // Lógica de reanimación
    return this;
}

State* RunningState::jump(Character& character, float time) {
    // Transición al estado de salto
    character.jump(time);
    return new JumpingState();
}

State* RunningState::specialAttack(Character& character, float time) {
    // Transición al estado de ataque especial
    return new SpecialAttackState();
}

State* RunningState::becomeIntoxicated(Character& character, float duration) {
    // Transición al estado de intoxicación
    return new IntoxicatedState(duration);
}

State* RunningState::stopAction() {
    // Transición al estado idle
    return new IdleState();
}
