#include "enemyWalking.h"
#include "enemyIdle.h"
#include "enemyAttacking.h"
#include "enemyReceivingDmg.h"
#include "enemyDead.h"


EnemyWalking::EnemyWalking(float time) : 
    timeToWalk(time) {
        enemyState = ENEMY_WALKING;
    }

std::unique_ptr<EnemyState> EnemyWalking::update(float time) {
    if (timeMoved == -1) {
        timeMoved = time;
    }
    if (time - timeMoved >= timeToWalk) {
        return std::make_unique<EnemyIdle>();
    }
    return nullptr;
}

std::unique_ptr<EnemyState> EnemyWalking::attackCharacter(Character* character, 
    int16_t dmg, float time) {
    return std::make_unique<EnemyAttacking>(character, dmg, time);
}

std::unique_ptr<EnemyState> EnemyWalking::receivingDmg(float time) {
    return std::make_unique<EnemyReceivingDmg>(time);
}

std::unique_ptr<EnemyState> EnemyWalking::die(float time) {
    return std::make_unique<EnemyDead>(time);
}

void EnemyWalking::setVelocity(float vel) {
    timeToWalk = vel;
}



