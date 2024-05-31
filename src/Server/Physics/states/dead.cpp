#include "dead.h"
#include "idle.h"
#include <utility>

State* DeadState::update(float time) {
    // No hay lógica de actualización para el estado de muerte
    return this;
}

State* DeadState::shoot(Character& character, Weapon* weapon, float time) {
    // No puede disparar estando muerto
    return this;
}

State* DeadState::move(Character& character, std::int16_t direction, float time) {
    // No puede moverse estando muerto
    return this;
}

State* DeadState::sprint(Character& character, float time) {
    // No puede correr estando muerto
    return this;
}

State* DeadState::reload(Weapon* weapon, float time) {
    // No puede recargar estando muerto
    return this;
}

State* DeadState::receiveDamage(Character& character, uint16_t dmg, float time) {
    // No recibe daño estando muerto
    return this;
}

State* DeadState::die(Character& character, float time) {
    // Ya está muerto
    return this;
}

State* DeadState::revive(Character& character, float time) {
    // Transición al estado de revivir
    return new IdleState();
}

State* DeadState::jump(Character& character, float time) {
    // No puede saltar estando muerto
    return this;
}

State* DeadState::specialAttack(Character& character, float time) {
    // No puede realizar ataques especiales estando muerto
    return this;
}

State* DeadState::becomeIntoxicated(Character& character, float duration) {
    // No puede intoxicarse estando muerto
    return this;
}

State* DeadState::stopAction() {
    // Permanecer en el estado de muerte
    return this;
}
