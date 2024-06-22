#include "shooting.h"
#include <vector>
#include "../character.h"
#include "damage.h"
#include "dead.h"
#include "idle.h"
#include "intoxicated.h"
#include "jumping.h"
#include "moving.h"

ShootingState::ShootingState(Character& character, const std::shared_ptr<Weapon>& weapon, float time)
    : character(character), weapon(weapon), shootCooldown(weapon->getFireRate()), startTime(time) {
    characterState = CharacterStateEntity::SHOOTING;
    std::cout << "[SHOOTING STATE] Created ShootingState" << std::endl;
}

std::unique_ptr<State> ShootingState::exec(float time) {
    std::cout << "Shooting state" << std::endl;
    return shoot(weapon, time);
}

std::unique_ptr<State> ShootingState::shoot(const std::shared_ptr<Weapon>& weapon, float time) {
    std::cout << "[SHOOTING] Shooting" << std::endl;
    if (!weapon->isEmpty() && (time - startTime) > shootCooldown) {
        startTime = time;
        std::vector<std::shared_ptr<Entity>> characters = character.getTargets();
        uint8_t x = character.getMapPosition(2).x;  // moves per cell
        std::cout << "shooting at " << x << std::endl;
        weapon->shoot(characters, x, time);
        return std::make_unique<IdleState>(character);  // Regresar a IdleState después de disparar
    }
    return nullptr;
}

std::unique_ptr<State> ShootingState::move(Direction direction, float time) {
    return std::make_unique<MovingState>(character, direction);
}

std::unique_ptr<State> ShootingState::sprint(Direction direction, float time) {
    return std::make_unique<MovingState>(character, direction);
}

std::unique_ptr<State> ShootingState::receiveDamage(uint8_t dmg, float time) {
    return std::make_unique<ReceivingDamageState>(character, time, dmg);
}

std::unique_ptr<State> ShootingState::die(float time) {
    return std::make_unique<DeadState>(character, time);
}

std::unique_ptr<State> ShootingState::revive(float time) {
    return nullptr;
}

std::unique_ptr<State> ShootingState::jump(float time) {
    return std::make_unique<JumpingState>(character);
}

std::unique_ptr<State> ShootingState::specialAttack(float time) {
    return nullptr;
}

std::unique_ptr<State> ShootingState::becomeIntoxicated(float duration) {
    return std::make_unique<IntoxicatedState>(character, duration);
}

std::unique_ptr<State> ShootingState::stopAction() {
    return std::make_unique<IdleState>(character);
}
