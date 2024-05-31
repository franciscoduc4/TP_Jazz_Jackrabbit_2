#include "shooting.h"
#include "idle_state.h"

State* ShootingState::update(float time) {
    // Lógica de actualización específica para el estado de disparo
    // Volver al estado idle después de disparar
    return new IdleState();
}

State* ShootingState::shoot(Character& character, Weapon* weapon, float time) {
    // Ya está disparando
    return this;
}

State* ShootingState::move(Character& character, std::int16_t direction, float time) {
    // Puede moverse mientras dispara
    character.setDir(direction);
    if (direction > 0) {
        character.moveToRight(time);
    } else {
        character.moveToLeft(time);
    }
    return this;
}

State* ShootingState::reload(Weapon* weapon, float time) {
    // Transición al estado de recarga
    return this;
}

State* ShootingState::receiveDamage(Character& character, uint16_t dmg, float time) {
    character.recvDmg(dmg, time);
    if (character.getHealth() <= 0) {
        return new DeadState();
    }
    return this;
}

State* ShootingState::die(Character& character, float time) {
    character.die(time);
    return new DeadState();
}

State* ShootingState::revive(Character& character, float time) {
    // Lógica de reanimación
    return this;
}

State* ShootingState::jump(Character& character, float time) {
    // Transición al estado de salto
    return new JumpingState();
}

State* ShootingState::specialAttack(Character& character, float time) {
    // Transición al estado de ataque especial
    return new SpecialAttackState();
}

State* ShootingState::becomeIntoxicated(Character& character, float duration) {
    // Transición al estado de intoxicación
    return new IntoxicatedState(duration);
}

State* ShootingState::stopAction() {
    // Transición al estado idle
    return new IdleState();
}
