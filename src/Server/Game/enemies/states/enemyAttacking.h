#ifndef ENEMY_ATTACKING_H
#define ENEMY_ATTACKING_H

#include <memory>

#include "enemyState.h"

class EnemyAttacking: public EnemyState {
private:
    float startTime;
    float waitingToAttack;

public:
    EnemyAttacking(std::shared_ptr<Character> target, int16_t damage, float attackTime);

    std::unique_ptr<EnemyState> update(float time) override;
    std::unique_ptr<EnemyState> attackCharacter(std::shared_ptr<Character> character, int16_t dmg,
                                                float time) override;
    std::unique_ptr<EnemyState> receivingDmg(float time) override;
    std::unique_ptr<EnemyState> die(float time) override;
    void setVelocity(float vel) override;
};

#endif  // ENEMY_ATTACKING_H
