#include "moving.h"

#include "../../../../Common/Types/direction.h"
#include "../../../../Common/Types/entity.h"
#include "../character.h"

#include "damage.h"
#include "dead.h"
#include "idle.h"
#include "intoxicated.h"
#include "moving.h"
#include "shooting.h"
#include "sprinting.h"

MovingState::MovingState(Character& character, Direction direction):
        character(character), direction(direction) {
    if (direction == Direction::UP) {
        characterState = CharacterStateEntity::JUMPING;
    } else {
        characterState = CharacterStateEntity::MOVING;
    }
}

std::unique_ptr<State> MovingState::exec(float time) {
    std::cout << "[MOVE] MovingState::exec" << std::endl;
    return move(direction, time);
}

std::unique_ptr<State> MovingState::shoot(const std::shared_ptr<Weapon>& weapon, float time) {
    if (time - lastTimeMoved >= waitingMoveTime) {
        return nullptr;
    }
    if (weapon->isEmpty()) {
        return std::unique_ptr<IdleState>();
    }
    return std::make_unique<ShootingState>(character, weapon, time);
}

std::unique_ptr<State> MovingState::move(Direction direction2, float time) {
    std::cout << "[MOVE] moving direction: " << static_cast<int>(direction2) << std::endl;
    switch (direction2) {
        case Direction::UP:
            character.jump(0);
            break;
        case Direction::DOWN:
            character.moveDown();
            break;
        case Direction::RIGHT:
            character.moveRight();
            break;
        case Direction::LEFT:
            character.moveLeft();
            break;
        default:
            break;
    }
    if (character.isOnGround() && direction2 == Direction::DOWN) {
        return std::make_unique<IdleState>(character);
    }
    return nullptr;
}


std::unique_ptr<State> MovingState::sprint(Direction direction2, float time) {
    // Cambia al estado de sprint
    return std::make_unique<SprintingState>(character, direction);
}

std::unique_ptr<State> MovingState::receiveDamage(uint8_t damage, float time) {
    // Maneja la recepción de daño
    return std::make_unique<ReceivingDamageState>(character, time, damage);
}

std::unique_ptr<State> MovingState::die(float respawnTime) {
    // Cambia al estado de muerte
    return std::make_unique<DeadState>(character, respawnTime);
}

std::unique_ptr<State> MovingState::revive(float time) {
    // Lógica de reanimación
    return nullptr;
}

std::unique_ptr<State> MovingState::becomeIntoxicated(float duration) {
    // Cambia al estado de intoxicación
    return std::make_unique<IntoxicatedState>(character, duration);
}

std::unique_ptr<State> MovingState::specialAttack(float time) {
    // Cambia al estado de ataque especial
    return std::make_unique<SpecialAttackState>(character, time);
}
std::unique_ptr<State> MovingState::jump(float time) {

    return std::make_unique<SpecialAttackState>(character, time);
}

std::unique_ptr<State> MovingState::stopAction() {
    // Cambia al estado inactivo
    return std::make_unique<IdleState>(character);
}
