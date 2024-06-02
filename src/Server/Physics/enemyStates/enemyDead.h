#ifndef ENEMY_DEAD_H
#define ENEMY_DEAD_H

#include "enemyState.h"
#include <memory>

class EnemyDead : public EnemyState {
    
private:

public:
    explicit EnemyDead(float deadTime);
    std::unique_ptr<EnemyState> update(float time) override;
    std::unique_ptr<EnemyState> attackCharacter(Character* character, 
    int16_t dmg, float time) override;
    std::unique_ptr<EnemyState> receivingDmg(float time) override;
    std::unique_ptr<EnemyState> die(float time) override;
    void setVelocity(float vel) override;
};

#endif // ENEMY_DEAD_H
