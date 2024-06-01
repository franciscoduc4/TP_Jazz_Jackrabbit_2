#include "move.h"
#include "idle.h"
#include "shooting.h"
#include "dead.h"
#include "intoxicated.h"
#include "damage.h"

#include "../playerCharacter.h"
#include "../../../Common/Types/move.h"
#include "../../../Common/Types/objectState.h"

MoveState::MoveState(Character& character, Move direction, float time) : 
        character(character), 
        direction(direction), 
        time(time) {
            characterState = CharacterState::MOVING;
            move(character, direction, time);
        }

State* MoveState::update(float time) {
    return move(character, direction, time);
}

State* MoveState::shoot(Character& character, Weapon* weapon, float time) {
    // Cambia al estado de disparo
    if (weapon->isEmpty()){
        return new IdleState();
    }
    return new ShootingState(character, weapon, time);
}

State* MoveState::move(Character& character, Move direction, float time) {
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

State* MoveState::reload(Weapon* weapon, float time) {
    // Cambia al estado de recarga
    return new IdleState();
}

State* MoveState::receiveDamage(Character& character, uint16_t damage, float time) {
    // Maneja la recepción de daño
    return new ReceivingDamageState(time);
}

State* MoveState::die(Character& character, float respawnTime) {
    // Cambia al estado de muerte
    return new DeadState(respawnTime);
}

State* MoveState::becomeIntoxicated(Character& character, float duration) {
    // Cambia al estado de intoxicación
    return new IntoxicatedState(duration);
}

// State* MoveState::jump(Character& character, float time) {
//     // Cambia al estado de salto
//     return new JumpingState();
// }

State* MoveState::stopAction() {
    // Cambia al estado inactivo
    return new IdleState();
}
