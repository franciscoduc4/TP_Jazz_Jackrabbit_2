#include "enemyIdle.h"

#include "enemyAttacking.h"
#include "enemyDead.h"
#include "enemyReceivingDmg.h"

std::unique_ptr<EnemyState> EnemyIdle::update(float time) { return nullptr; }

std::unique_ptr<EnemyState> EnemyIdle::attackCharacter(std::shared_ptr<Character> character,
                                                       int16_t dmg, float time) {
    return std::make_unique<EnemyAttacking>(character, dmg, time);
}

std::unique_ptr<EnemyState> EnemyIdle::receivingDmg(float time) {
    return std::make_unique<EnemyReceivingDmg>(time);
}

std::unique_ptr<EnemyState> EnemyIdle::die(float time) { return std::make_unique<EnemyDead>(time); }

void EnemyIdle::setVelocity(float vel) {}
