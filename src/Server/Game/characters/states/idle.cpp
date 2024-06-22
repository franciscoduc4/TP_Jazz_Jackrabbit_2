#include "idle.h"

#include "../character.h"

#include "damage.h"
#include "dead.h"
#include "intoxicated.h"
#include "jumping.h"
#include "moving.h"
#include "shooting.h"
#include "specialAttack.h"

IdleState::IdleState(Character& character) : character(character){ characterState = IDLE; }

std::unique_ptr<State> IdleState::exec(float time) {
    std::cout << "[IDLE] Executing idle state for character ID: " << static_cast<int>(character.getId()) << std::endl;
    if (!character.isOnGround()) {
        return std::make_unique<MovingState>(character, Direction::DOWN);
    }
    return nullptr;
}

std::unique_ptr<State> IdleState::shoot(const std::shared_ptr<Weapon>& weapon,
                                        float time) {
                                       
    std::cout << "[IDLE STATE SHOOT] Shooting" << std::endl;                            
    if (!weapon) {
        std::cerr << "[IDLE STATE] Error: weapon is null" << std::endl;
        return nullptr;
    }

    // if (weapon->isEmpty() || !weapon->cooldown(time)) {
    //     std::cout << "[IDLE STATE] Weapon is empty or in cooldown" << std::endl;
    //     return nullptr;
    // }
    return std::make_unique<ShootingState>(character, weapon, time);
}

std::unique_ptr<State> IdleState::move(Direction direction, float time) {
    return std::make_unique<MovingState>(character, direction);
}

std::unique_ptr<State> IdleState::sprint(Direction direction, float time) {

    return nullptr;
}


std::unique_ptr<State> IdleState::receiveDamage(uint8_t dmg, float time) {
    return std::make_unique<ReceivingDamageState>(character, time, dmg);
}

std::unique_ptr<State> IdleState::die(float time) {
    return std::make_unique<DeadState>(character, time);
}

std::unique_ptr<State> IdleState::revive(float time) { return nullptr; }

std::unique_ptr<State> IdleState::jump(float time) {
    return std::make_unique<JumpingState>(character);
}

std::unique_ptr<State> IdleState::specialAttack(float time) {
    return std::make_unique<SpecialAttackState>(character, time);
}

std::unique_ptr<State> IdleState::becomeIntoxicated(float duration) {
    return std::make_unique<IntoxicatedState>(character, duration);
}

std::unique_ptr<State> IdleState::stopAction() { return nullptr; }
