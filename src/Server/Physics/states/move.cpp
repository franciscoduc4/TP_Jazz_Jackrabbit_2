#include "move.h"
#include "idle.h"
#include "shooting.h"
#include "dead.h"
#include "intoxicated.h"
#include "damage.h"

#include "../playerCharacter.h"
#include "../../../Common/Types/move.h"
#include "../../../Common/Types/entity.h"

MoveState::MoveState(Character& character, Move direction, float time) : 
        character(character), 
        direction(direction), 
        time(time) {
            characterState = CharacterStateEntity::MOVING;
            move(character, direction, time);
        }

std::unique_ptr<State> MoveState::update(float time) {
    return move(character, direction, time);
}

std::unique_ptr<State> MoveState::shoot(Character& character, 
std::unique_ptr<Weapon> weapon, float time) {
    // Cambia al estado de disparo
    if (weapon->isEmpty()){
        return std::unique_ptr<IdleState>();
    }
    return std::make_unique<ShootingState>(character, weapon, time);
}

std::unique_ptr<State> MoveState::move(Character& character, Move direction, float time) {
    // Actualiza la dirección del movimiento
    switch (direction) {
        case Move::UP:
            character.moveUp();
            break;
        case Move::DOWN:
            character.moveRight();
            break;
        case Move::RIGHT:
            character.moveRight();
            break;
        case Move::LEFT:
            character.moveLeft();
            break;
        default:
            break;
    }
    return nullptr;

}

std::unique_ptr<State> MoveState::reload(std::unique_ptr<Weapon> weapon, float time) {
    // Cambia al estado de recarga
    return std::unique_ptr<IdleState>();
}

std::unique_ptr<State> MoveState::receiveDamage(Character& character, uint16_t damage, float time) {
    // Maneja la recepción de daño
    return std::make_unique<ReceivingDamageState>(time);
}

std::unique_ptr<State> MoveState::die(Character& character, float respawnTime) {
    // Cambia al estado de muerte
    return std::make_unique<DeadState>(respawnTime);
}

std::unique_ptr<State> MoveState::becomeIntoxicated(Character& character, float duration) {
    // Cambia al estado de intoxicación
    return std::make_unique<IntoxicatedState>(duration);
}

// std::unique_ptr<State> MoveState::jump(Character& character, float time) {
//     // Cambia al estado de salto
//     return std::unique_ptr<JumpingState>();
// }

std::unique_ptr<State> MoveState::stopAction() {
    // Cambia al estado inactivo
    return std::unique_ptr<IdleState>();
}
