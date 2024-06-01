#include "intoxicated.h"
#include "idle.h"
#include "dead.h"

State* IntoxicatedState::update(float time) {
    intoxicatedDuration -= time;
    if (intoxicatedDuration <= 0) {
        return new IdleState();
    }
    return this;
}

State* IntoxicatedState::shoot(Character& character, Weapon* weapon, float time) {
    // No puede disparar mientras está intoxicado
    return nullptr;
}

State* IntoxicatedState::move(Character& character, Move direction, float time) {
    // Puede moverse lentamente mientras está intoxicado
    //character.move(direction * 0.5f, time);  // Se mueve a la mitad de la velocidad normal
    return nullptr;
}

State* IntoxicatedState::sprint(Character& character, float time) {
    // No puede correr mientras está intoxicado
    return nullptr;
}

State* IntoxicatedState::reload(Weapon* weapon, float time) {
    // No puede recargar mientras está intoxicado
    return nullptr;
}

State* IntoxicatedState::receiveDamage(Character& character, uint16_t dmg, float time) {
    // character->recvDmg(dmg, time);
    // if (character.getHealth() <= 0) {
    //     return new DeadState(time);
    // }
    return nullptr;
}

State* IntoxicatedState::die(Character& character, float time) {
    return new DeadState(time);
}

State* IntoxicatedState::revive(Character& character, float time) {
    // Lógica de reanimación
    return this;
}

State* IntoxicatedState::jump(Character& character, float time) {
    // Puede saltar pero con menos altura
    //character.jump(time * 0.5f);  // Salta a la mitad de la altura normal
    return this;
}

State* IntoxicatedState::specialAttack(Character& character, float time) {
    // No puede realizar ataques especiales mientras está intoxicado
    return nullptr;
}

State* IntoxicatedState::becomeIntoxicated(Character& character, float duration) {
    // Extender la duración de la intoxicación
    intoxicatedDuration += duration;
    return nullptr;
}

State* IntoxicatedState::stopAction() {
    // Permanecer en el estado de intoxicación
    return nullptr;
}
