#include "jumping.h"
#include "../character.h"
#include "dead.h"
#include "idle.h"
#include "intoxicated.h"
#include "moving.h"
#include "shooting.h"

#include <iostream>

JumpingState::JumpingState(Character& character) : character(character) {
    characterState = CharacterStateEntity::JUMPING;
}

std::unique_ptr<State> JumpingState::exec(float time) {

    if (!character.isAlive()){
        return nullptr;
    }

    if (!character.isJumping()) {
        character.jump(time);
    }

    if (character.hasLanded()) {
        return std::make_unique<IdleState>(character);
    }

    return nullptr;
}

std::unique_ptr<State> JumpingState::shoot(const std::shared_ptr<Weapon>& weapon, float time) {
    return nullptr;
}

std::unique_ptr<State> JumpingState::move(Direction direction, float time) {
    // Puede moverse en el aire
    return std::make_unique<MovingState>(character, direction);
}

std::unique_ptr<State> JumpingState::sprint(Direction direction, float time) {
    // No puede correr mientras está en el aire
    return nullptr;
}

std::unique_ptr<State> JumpingState::receiveDamage(uint8_t dmg, float time) {
    character.recvDamage(dmg, time);
    if (character.getHealth() <= 0) {
        return std::make_unique<DeadState>(character, time);
    }
    return nullptr;
}

std::unique_ptr<State> JumpingState::die(float time) {
    character.die(time);
    return std::make_unique<DeadState>(character, time);
}

std::unique_ptr<State> JumpingState::revive(float time) {
    // Lógica de reanimación
    return nullptr;
}

std::unique_ptr<State> JumpingState::jump(float time) {
    // Puede saltar mientras está en el aire
    std::cout << "JumpingState::jump" << std::endl;
    if (!character.isJumping()) {
        character.jump(time);
    }
    // if (character.hasLanded()) {
    //     return std::make_unique<IdleState>();
    // }
    return nullptr;
}

std::unique_ptr<State> JumpingState::specialAttack(float time) {
    // Puede realizar un ataque especial mientras está en el aire
    return nullptr;
}

std::unique_ptr<State> JumpingState::becomeIntoxicated(float duration) {
    // Puede intoxicarse mientras está en el aire
    return std::make_unique<IntoxicatedState>(character, duration);
}

std::unique_ptr<State> JumpingState::stopAction() {
    // Transición al estado idle
    return std::make_unique<IdleState>(character);
}
