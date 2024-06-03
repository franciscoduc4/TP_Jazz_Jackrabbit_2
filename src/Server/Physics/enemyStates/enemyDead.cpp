#include "enemyDead.h"

EnemyDead::EnemyDead(float deadTime) { enemyState = ENEMY_DEAD; }

std::unique_ptr<EnemyState> EnemyDead::update(float time) { return nullptr; }

std::unique_ptr<EnemyState> EnemyDead::attackCharacter(std::shared_ptr<Character> character,
                                                       int16_t dmg, float time) {
    return nullptr;
}

std::unique_ptr<EnemyState> EnemyDead::receivingDmg(float time) { return nullptr; }

std::unique_ptr<EnemyState> EnemyDead::die(float time) { return nullptr; }

void EnemyDead::setVelocity(float vel) {}
