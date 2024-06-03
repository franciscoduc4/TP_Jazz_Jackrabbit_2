#ifndef ENEMY_IDLE_H
#define ENEMY_IDLE_H

#include <memory>

#include "enemyState.h"

class EnemyIdle: public EnemyState {
public:
    std::unique_ptr<EnemyState> update(float time) override;
    std::unique_ptr<EnemyState> attackCharacter(std::shared_ptr<Character> character, int16_t dmg,
                                                float time) override;
    std::unique_ptr<EnemyState> receivingDmg(float time) override;
    std::unique_ptr<EnemyState> die(float time) override;
    void setVelocity(float vel) override;
};

#endif  // ENEMY_IDLE_H
