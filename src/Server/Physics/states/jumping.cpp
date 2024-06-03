#include "jumping.h"

#include "../playerCharacter.h"

#include "dead.h"
#include "idle.h"
#include "intoxicated.h"
#include "moving.h"
#include "shooting.h"

std::unique_ptr<State> JumpingState::update(float time) {
    // Lógica de actualización específica para el estado de salto
    // Transición al estado idle si ha aterrizado
    return std::unique_ptr<IdleState>();
}

std::unique_ptr<State> JumpingState::shoot(Character& character, std::shared_ptr<Weapon> weapon,
                                           float time) {
    // Puede disparar mientras está en el aire
    // Lógica para disparar
    return nullptr;
}

std::unique_ptr<State> JumpingState::move(Character& character, Direction direction, float time) {
    // Puede moverse en el aire
    // character.setDir(direction);
    // if (direction > 0) {
    //     character.moveToRight(time);
    // } else {
    //     character.moveToLeft(time);
    // }
    return nullptr;
}

std::unique_ptr<State> JumpingState::sprint(Character& character, float time) {
    // No puede correr mientras está en el aire
    return nullptr;
}

std::unique_ptr<State> JumpingState::reload(std::shared_ptr<Weapon> weapon, float time) {
    // No puede recargar mientras está en el aire
    return nullptr;
}

std::unique_ptr<State> JumpingState::receiveDamage(Character& character, uint16_t dmg, float time) {
    character.recvDamage(dmg, time);
    if (character.getHealth() <= 0) {
        return std::make_unique<DeadState>(time);
    }
    return nullptr;
}

std::unique_ptr<State> JumpingState::die(Character& character, float time) {
    character.die(time);
    return std::make_unique<DeadState>(time);
}

std::unique_ptr<State> JumpingState::revive(Character& character, float time) {
    // Lógica de reanimación
    return nullptr;
}

std::unique_ptr<State> JumpingState::jump(Character& character, float time) {
    // Ya está en el aire, no puede saltar de nuevo
    return nullptr;
}

// std::unique_ptr<State> JumpingState::specialAttack(Character& character, float time) {
//     // Puede realizar un ataque especial mientras está en el aire
//     return new SpecialAttackState();
// }

std::unique_ptr<State> JumpingState::becomeIntoxicated(Character& character, float duration) {
    // Puede intoxicarse mientras está en el aire
    return std::make_unique<IntoxicatedState>(duration);
}

std::unique_ptr<State> JumpingState::stopAction() {
    // Transición al estado idle
    return std::unique_ptr<IdleState>();
}
