#include "enemyAttacking.h"

#include "../../characters/character.h"

#include "enemyDead.h"
#include "enemyIdle.h"
#include "enemyReceivingDmg.h"


EnemyAttacking::EnemyAttacking(std::shared_ptr<Character> target, int16_t damage, float attackTime):
        startTime(attackTime), waitingToAttack(0.5f) {
    enemyState = ENEMY_ATTACKING;
    target->recvDamage(damage, attackTime);
}

std::unique_ptr<EnemyState> EnemyAttacking::update(float time) {
    if (time - startTime > waitingToAttack) {
        return std::make_unique<EnemyIdle>();
    }
    return nullptr;
}

std::unique_ptr<EnemyState> EnemyAttacking::attackCharacter(std::shared_ptr<Character> character,
                                                            int16_t dmg, float time) {
    if (time - startTime > waitingToAttack) {
        startTime = time;
        character->recvDamage(dmg, time);
    }
    return nullptr;
}

std::unique_ptr<EnemyState> EnemyAttacking::receivingDmg(float time) {
    return std::make_unique<EnemyReceivingDmg>(time);
}

std::unique_ptr<EnemyState> EnemyAttacking::die(float time) {
    return std::make_unique<EnemyDead>(time);
}

void EnemyAttacking::setVelocity(float vel) { waitingToAttack = vel; }
