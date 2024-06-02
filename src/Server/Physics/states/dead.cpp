#include "dead.h"
#include "idle.h"
#include <utility>

DeadState::DeadState(float deathTime):
    startTime(deathTime),
    reviveTime(3) { //CONFIG.getReviveTime()
        characterState = CharacterStateEntity::DEAD;
    }

std::unique_ptr<State> DeadState::update(float time) {
    // No hay lógica de actualización para el estado de muerte
    return nullptr;
}

std::unique_ptr<State> DeadState::shoot(Character& character, 
    std::unique_ptr<Weapon> weapon, float time) {
    // No puede disparar estando muerto
    return nullptr;
}

std::unique_ptr<State> DeadState::move(Character& character, Move direction, float time) {
    // No puede moverse estando muerto
    return nullptr;
}

std::unique_ptr<State> DeadState::sprint(Character& character, float time) {
    // No puede correr estando muerto
    return nullptr;
}

std::unique_ptr<State> DeadState::reload(std::unique_ptr<Weapon> weapon, float time) {
    // No puede recargar estando muerto
    return nullptr;
}

std::unique_ptr<State> DeadState::receiveDamage(Character& character, uint16_t dmg, float time) {
    // No recibe daño estando muerto
    return nullptr;
}

std::unique_ptr<State> DeadState::die(Character& character, float time) {
    // Ya está muerto
    return nullptr;
}

std::unique_ptr<State> DeadState::revive(Character& character, float time) {
    if (time < reviveTime + startTime){
        return std::unique_ptr<IdleState>();
    }
    return nullptr;
}

std::unique_ptr<State> DeadState::jump(Character& character, float time) {
    // No puede saltar estando muerto
    return nullptr;
}

std::unique_ptr<State> DeadState::specialAttack(Character& character, float time) {
    // No puede realizar ataques especiales estando muerto
    return nullptr;
}

std::unique_ptr<State> DeadState::becomeIntoxicated(Character& character, float duration) {
    // No puede intoxicarse estando muerto
    return nullptr;
}

std::unique_ptr<State> DeadState::stopAction() {
    // Permanecer en el estado de muerte
    return nullptr;
}

