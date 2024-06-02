#ifndef ENEMY_ATTACKING_H
#define ENEMY_ATTACKING_H

#include "enemyState.h"
#include <memory>

class EnemyAttacking : public EnemyState {
private:
    float startTime;
    float waitingToAttack;

public:
    EnemyAttacking(Character* target, int16_t damage, float attackTime);

    std::unique_ptr<EnemyState> update(float time) override;
    std::unique_ptr<EnemyState> attackCharacter(Character* character, 
    int16_t dmg, float time) override;
    std::unique_ptr<EnemyState> receivingDmg(float time) override;
    std::unique_ptr<EnemyState> die(float time) override;
    void setVelocity(float vel) override;
};

#endif // ENEMY_ATTACKING_H
