#include "shooting.h"
#include "idle.h"
#include "jumping.h"
#include "intoxicated.h"
#include "dead.h"
#include "move.h"
#include "../playerCharacter.h"
#include <vector>

ShootingState::ShootingState(Character& character, std::unique_ptr<Weapon> weapon, float time): 
    character(character), 
    weapon(weapon) {
    characterState = CharacterStateEntityEntity::SHOOTING;
    shoot(character, weapon, time);
}

std::unique_ptr<State> ShootingState::update(float time) {
    // Lógica de actualización específica para el estado de disparo
    // Volver al estado idle después de disparar
    return std::make_unique<IdleState>();
}

std::unique_ptr<State> ShootingState::shoot(Character& character, 
    std::unique_ptr<Weapon> weapon, float time) {
    // Ya está disparando
    if (!weapon->isEmpty() && (time - startTime) > waitToShoot){
        startTime = time; 
        std::vector<std::shared_ptr<Entity>> characters = character.getTargets();
        int16_t x = character.getMatrixX();
        weapon->shoot(characters, x, time);
    }
    return nullptr;
}

std::unique_ptr<State> ShootingState::move(Character& character, Move direction, float time) {
    // Puede moverse mientras dispara
    return std::make_unique<MoveState>(character, direction, time);
}

std::unique_ptr<State> ShootingState::reload(std::unique_ptr<Weapon> weapon, float time) {
    // Transición al estado de recarga
    return std::unique_ptr<State>(this);
}

std::unique_ptr<State> ShootingState::receiveDamage(Character& character, uint16_t dmg, float time) {
    character.recvDamage(dmg, time);
    if (character.getHealth() <= 0) {
        return std::make_unique<DeadState>();
    }
    return std::unique_ptr<State>(this);
}

std::unique_ptr<State> ShootingState::die(Character& character, float time) {
    character.die(time);
    return std::make_unique<DeadState>();
}

std::unique_ptr<State> ShootingState::revive(Character& character, float time) {
    // Lógica de reanimación
    return std::unique_ptr<State>(this);
}

std::unique_ptr<State> ShootingState::jump(Character& character, float time) {
    // Transición al estado de salto
    return std::make_unique<JumpingState>();
}

// std::unique_ptr<State> ShootingState::specialAttack(Character& character, float time) {
//     // Transición al estado de ataque especial
//     return std::make_unique<SpecialAttackState>();
// }

std::unique_ptr<State> ShootingState::becomeIntoxicated(Character& character, float duration) {
    // Transición al estado de intoxicación
    return std::make_unique<IntoxicatedState>(duration);
}

std::unique_ptr<State> ShootingState::stopAction() {
    // Transición al estado idle
    return std::make_unique<IdleState>();
}
