#include "shooting.h"

#include <vector>

#include "../character.h"

#include "damage.h"
#include "dead.h"
#include "idle.h"
#include "intoxicated.h"
#include "jumping.h"
#include "moving.h"

ShootingState::ShootingState(Character& character, const std::shared_ptr<Weapon>& weapon, float time):
        character(character), weapon(weapon), shootCooldown(weapon->getFireRate()) {
    characterState = CharacterStateEntity::SHOOTING;
}

std::unique_ptr<State> ShootingState::exec(float time) {
    std::cout << "Shooting state" << std::endl;
    return shoot(weapon, time);
}

std::unique_ptr<State> ShootingState::shoot(const std::shared_ptr<Weapon>& weapon,
                                            float time) {

    if (!weapon->isEmpty() && (time - startTime) > shootCooldown) {
        startTime = time;
        std::vector<std::shared_ptr<Entity>> characters = character.getTargets();
        uint8_t x = character.getMapPosition(2).x;  // moves per cell
        std::cout << "shooting at " << x << std::endl;
        weapon->shoot(characters, x, time);
        return std::unique_ptr<ShootingState>();
    }
    return nullptr;
}

std::unique_ptr<State> ShootingState::move(Direction direction, float time) {
    // Puede moverse mientras dispara
    return std::make_unique<MovingState>(character, direction);
}


std::unique_ptr<State> ShootingState::sprint(Direction direction,
                                             float time) {
    // Cambia al estado de sprint
    return std::make_unique<MovingState>(character, direction);
}

std::unique_ptr<State> ShootingState::receiveDamage(uint8_t dmg,
                                                    float time) {

    return std::make_unique<ReceivingDamageState>(character, time, dmg);
}

std::unique_ptr<State> ShootingState::die(float time) {
    // character.die(time);
    return std::make_unique<DeadState>(character, time);
}

std::unique_ptr<State> ShootingState::revive(float time) {
    // Lógica de reanimación
    return nullptr;
}

std::unique_ptr<State> ShootingState::jump(float time) {
    // Transición al estado de salto
    return std::make_unique<JumpingState>(character);
}

std::unique_ptr<State> ShootingState::specialAttack(float time) {
    // Cambia al estado de sprint
    return nullptr;
}


std::unique_ptr<State> ShootingState::becomeIntoxicated(float duration) {
    // Transición al estado de intoxicación
    return std::make_unique<IntoxicatedState>(character, duration);
}

std::unique_ptr<State> ShootingState::stopAction() {
    // Transición al estado idle
    return std::make_unique<IdleState>(character);
}
