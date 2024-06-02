#include "enemyJumping.h"
#include "enemyIdle.h"
#include "enemyAttacking.h"
#include "enemyReceivingDmg.h"
#include "enemyDead.h"

EnemyJumping::EnemyJumping(float time) : 
    timeToJump(1) {
        enemyState = ENEMY_JUMPING;
    }

std::unique_ptr<EnemyState> EnemyJumping::update(float time) {
    return nullptr;
}

std::unique_ptr<EnemyState> EnemyJumping::attackCharacter(Character* character, 
    int16_t dmg, float time) {
    if (time - timeJumped > timeToJump) {
        return std::make_unique<EnemyAttacking>(character, dmg, time);
    }
    return nullptr;
}

std::unique_ptr<EnemyState> EnemyJumping::receivingDmg(float time) {
    return std::make_unique<EnemyReceivingDmg>(time);
}

std::unique_ptr<EnemyState> EnemyJumping::die(float time) {
    return std::make_unique<EnemyDead>(time);
}

void EnemyJumping::setVelocity(float vel) {
    timeToJump = vel;
}




