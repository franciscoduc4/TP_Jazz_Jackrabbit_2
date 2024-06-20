#include "intoxicated.h"

#include "dead.h"
#include "idle.h"

IntoxicatedState::IntoxicatedState(Character& character, float duration):
        intoxicatedDuration(duration),
        character(character) {
    characterState = CharacterStateEntity::INTOXICATED;
}

std::unique_ptr<State> IntoxicatedState::exec(float time) {
    intoxicatedDuration -= time;
    if (intoxicatedDuration <= 0) {
        return std::unique_ptr<IdleState>();
    }
    return nullptr;
}

std::unique_ptr<State> IntoxicatedState::shoot(const std::shared_ptr<Weapon>& weapon,
                                               float time) {
    // No puede disparar mientras está intoxicado
    return nullptr;
}

std::unique_ptr<State> IntoxicatedState::move(Direction direction,
                                              float time) {
    // Puede moverse lentamente mientras está intoxicado
    // character.move(direction * 0.5f, time);  // Se mueve a la mitad de la velocidad normal
    return nullptr;
}

std::unique_ptr<State> IntoxicatedState::sprint(Direction direction,
                                                float time) {
    return nullptr;
}


std::unique_ptr<State> IntoxicatedState::receiveDamage(uint8_t dmg,
                                                       float time) {
    // character->recvDmg(dmg, time);
    // if (character.getHealth() <= 0) {
    //     return std::unique_ptr<DeadState>(time);
    // }
    return nullptr;
}

std::unique_ptr<State> IntoxicatedState::die(float time) {
    return std::make_unique<DeadState>(character, time);
}

std::unique_ptr<State> IntoxicatedState::revive(float time) {
    // Lógica de reanimación
    return nullptr;
}

std::unique_ptr<State> IntoxicatedState::jump(float time) {
    // Puede saltar pero con menos altura
    // character.jump(time * 0.5f);  // Salta a la mitad de la altura normal
    return nullptr;
}

std::unique_ptr<State> IntoxicatedState::specialAttack(float time) {
    // No puede realizar ataques especiales mientras está intoxicado
    return nullptr;
}

std::unique_ptr<State> IntoxicatedState::becomeIntoxicated(float duration) {
    // Extender la duración de la intoxicación
    intoxicatedDuration += duration;
    return nullptr;
}

std::unique_ptr<State> IntoxicatedState::stopAction() {
    // Permanecer en el estado de intoxicación
    return nullptr;
}
