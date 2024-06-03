#ifndef ENEMY_DEAD_H
#define ENEMY_DEAD_H

#include <memory>

#include "enemyState.h"

class EnemyDead: public EnemyState {

private:
public:
    explicit EnemyDead(float deadTime);
    std::unique_ptr<EnemyState> update(float time) override;
    std::unique_ptr<EnemyState> attackCharacter(std::shared_ptr<Character> character, int16_t dmg,
                                                float time) override;
    std::unique_ptr<EnemyState> receivingDmg(float time) override;
    std::unique_ptr<EnemyState> die(float time) override;
    void setVelocity(float vel) override;
};

#endif  // ENEMY_DEAD_H
