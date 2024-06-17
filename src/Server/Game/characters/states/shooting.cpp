#include "shooting.h"

#include <vector>

#include "../character.h"

#include "dead.h"
#include "idle.h"
#include "intoxicated.h"
#include "jumping.h"
#include "moving.h"

ShootingState::ShootingState(Character& character, std::shared_ptr<Weapon> weapon, float time):
        character(character), weapon(weapon) {
    characterState = CharacterStateEntity::SHOOTING;
    shoot(character, weapon, time);
}

std::unique_ptr<State> ShootingState::exec(Character& character, float time) {
    // Lógica de actualización específica para el estado de disparo
    // Volver al estado idle después de disparar
    return std::make_unique<IdleState>();
}

std::unique_ptr<State> ShootingState::shoot(Character& character, std::shared_ptr<Weapon> weapon,
                                            float time) {
    // Ya está disparando
    if (!weapon->isEmpty() && (time - startTime) > waitToShoot) {
        startTime = time;
        std::vector<std::shared_ptr<Entity>> characters = character.getTargets();
        // int16_t x = character.getMatrixX();
        // weapon->shoot(characters, x, time);
    }
    return nullptr;
}

std::unique_ptr<State> ShootingState::move(Character& character, Direction direction, float time) {
    // Puede moverse mientras dispara
    return std::make_unique<MovingState>(character, direction, time);
}


std::unique_ptr<State> ShootingState::sprint(Character& character, Direction direction,
                                             float time) {
    // Cambia al estado de sprint
    return std::unique_ptr<MovingState>();
}

std::unique_ptr<State> ShootingState::receiveDamage(Character& character, uint16_t dmg,
                                                    float time) {
    character.recvDamage(dmg, time);
    if (character.getHealth() <= 0) {
        return std::make_unique<DeadState>(time);
    }
    return std::unique_ptr<State>(this);
}

std::unique_ptr<State> ShootingState::die(Character& character, float time) {
    character.die(time);
    return std::make_unique<DeadState>(time);
}

std::unique_ptr<State> ShootingState::revive(Character& character, float time) {
    // Lógica de reanimación
    return std::unique_ptr<State>(this);
}

std::unique_ptr<State> ShootingState::jump(Character& character, float time) {
    // Transición al estado de salto
    return std::make_unique<JumpingState>();
}

std::unique_ptr<State> ShootingState::specialAttack(Character& character, float time) {
    // Cambia al estado de sprint
    return nullptr;
}


std::unique_ptr<State> ShootingState::becomeIntoxicated(Character& character, float duration) {
    // Transición al estado de intoxicación
    return std::make_unique<IntoxicatedState>(duration);
}

std::unique_ptr<State> ShootingState::stopAction() {
    // Transición al estado idle
    return std::make_unique<IdleState>();
}
