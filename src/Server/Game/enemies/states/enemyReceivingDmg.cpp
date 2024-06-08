#include "enemyReceivingDmg.h"

#include "enemyAttacking.h"
#include "enemyDead.h"
#include "enemyIdle.h"

EnemyReceivingDmg::EnemyReceivingDmg(float time): startTime(time), timeReceivedDmg(1) {
    enemyState = ENEMY_RECEIVING_DAMAGE;
}

std::unique_ptr<EnemyState> EnemyReceivingDmg::update(float time) {
    if (time - startTime > timeReceivedDmg) {
        return std::make_unique<EnemyIdle>();
    }
    return nullptr;
}

std::unique_ptr<EnemyState> EnemyReceivingDmg::attackCharacter(std::shared_ptr<Character> character,
                                                               int16_t dmg, float time) {
    if (time - startTime > timeReceivedDmg) {
        return std::make_unique<EnemyAttacking>(character, dmg, time);
    }
    return nullptr;
}

std::unique_ptr<EnemyState> EnemyReceivingDmg::receivingDmg(float time) {
    startTime = time;
    return nullptr;
}

std::unique_ptr<EnemyState> EnemyReceivingDmg::die(float time) {
    return std::make_unique<EnemyDead>(time);
}

void EnemyReceivingDmg::setVelocity(float vel) {}
