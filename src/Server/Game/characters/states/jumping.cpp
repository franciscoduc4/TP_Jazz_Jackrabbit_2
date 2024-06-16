#include "jumping.h"
#include "../character.h"
#include "dead.h"
#include "idle.h"
#include "intoxicated.h"
#include "moving.h"
#include "shooting.h"

std::unique_ptr<State> JumpingState::exec(Character& character, float time) {
    character.updatePosition(static_cast<float>(clock()) / CLOCKS_PER_SEC);  // Actualiza la posición del personaje según la física del salto

    if (!character.isJumping()) {  // Verifica si el personaje ha terminado de saltar
        return std::make_unique<IdleState>();
    }

    return nullptr;
}

std::unique_ptr<State> JumpingState::shoot(Character& character, std::shared_ptr<Weapon> weapon, float time) {
    // Puede disparar mientras está en el aire
    character.shoot(time);
    return nullptr;
}

std::unique_ptr<State> JumpingState::move(Character& character, Direction direction, float time) {
    // Puede moverse en el aire
    character.moveInAir(direction, time);  // Función específica para movimiento en el aire
    return nullptr;
}

std::unique_ptr<State> JumpingState::sprint(Character& character, Direction direction, float time) {
    // No puede correr mientras está en el aire
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

std::unique_ptr<State> JumpingState::specialAttack(Character& character, float time) {
    // Puede realizar un ataque especial mientras está en el aire
    return nullptr;
}

std::unique_ptr<State> JumpingState::becomeIntoxicated(Character& character, float duration) {
    // Puede intoxicarse mientras está en el aire
    return std::make_unique<IntoxicatedState>(duration);
}

std::unique_ptr<State> JumpingState::stopAction() {
    // Transición al estado idle
    return std::make_unique<IdleState>();
}
