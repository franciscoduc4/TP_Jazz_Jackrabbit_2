#include "moving.h"

#include "../../../Common/Types/direction.h"
#include "../../../Common/Types/entity.h"
#include "../playerCharacter.h"

#include "damage.h"
#include "dead.h"
#include "idle.h"
#include "intoxicated.h"
#include "moving.h"
#include "shooting.h"

MovingState::MovingState(Character& character, Direction direction, float time):
        character(character), direction(direction), time(time) {
    characterState = CharacterStateEntity::MOVING;
    move(character, direction, time);
}

std::unique_ptr<State> MovingState::update(float time) { return move(character, direction, time); }

std::unique_ptr<State> MovingState::shoot(Character& character, std::shared_ptr<Weapon> weapon,
                                          float time) {
    // Cambia al estado de disparo
    if (weapon->isEmpty()) {
        return std::unique_ptr<IdleState>();
    }
    return std::make_unique<ShootingState>(character, weapon, time);
}

std::unique_ptr<State> MovingState::move(Character& character, Direction direction, float time) {
    // Actualiza la dirección del movimiento
    switch (direction) {
        case Direction::UP:
            character.moveUp();
            break;
        case Direction::DOWN:
            character.moveRight();
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
    return nullptr;
}

std::unique_ptr<State> MovingState::reload(std::shared_ptr<Weapon> weapon, float time) {
    // Cambia al estado de recarga
    return std::unique_ptr<IdleState>();
}

std::unique_ptr<State> MovingState::receiveDamage(Character& character, uint16_t damage,
                                                  float time) {
    // Maneja la recepción de daño
    return std::make_unique<ReceivingDamageState>(time);
}

std::unique_ptr<State> MovingState::die(Character& character, float respawnTime) {
    // Cambia al estado de muerte
    return std::make_unique<DeadState>(respawnTime);
}

std::unique_ptr<State> MovingState::becomeIntoxicated(Character& character, float duration) {
    // Cambia al estado de intoxicación
    return std::make_unique<IntoxicatedState>(duration);
}

// std::unique_ptr<State> MovingState::jump(Character& character, float time) {
//     // Cambia al estado de salto
//     return std::unique_ptr<JumpingState>();
// }

std::unique_ptr<State> MovingState::stopAction() {
    // Cambia al estado inactivo
    return std::unique_ptr<IdleState>();
}
