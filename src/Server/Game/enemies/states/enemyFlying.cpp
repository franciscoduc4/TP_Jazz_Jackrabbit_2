#include "enemyFlying.h"

#include "enemyAttacking.h"
#include "enemyDead.h"
#include "enemyIdle.h"
#include "enemyReceivingDmg.h"


EnemyFlying::EnemyFlying(float time): timeToFly(0.2f) { enemyState = ENEMY_FLYING; }

std::unique_ptr<EnemyState> EnemyFlying::update(float time) {
    if (timeMoved == -1) {
        timeMoved = time;
    }
    if (time - timeMoved > timeToFly) {
        return std::make_unique<EnemyIdle>();
    }
    return nullptr;
}

std::unique_ptr<EnemyState> EnemyFlying::attackCharacter(std::shared_ptr<Character> character,
                                                         int16_t dmg, float time) {
    if (time - timeMoved > timeToFly) {
        return std::make_unique<EnemyAttacking>(character, dmg, time);
    }
    return nullptr;
}

std::unique_ptr<EnemyState> EnemyFlying::receivingDmg(float time) {
    return std::make_unique<EnemyReceivingDmg>(time);
}

std::unique_ptr<EnemyState> EnemyFlying::die(float time) {
    return std::make_unique<EnemyDead>(time);
}

void EnemyFlying::setVelocity(float vel) { timeToFly = vel; }
