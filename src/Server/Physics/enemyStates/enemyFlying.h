#ifndef ENEMY_FLYING_H
#define ENEMY_FLYING_H

#include <memory>

#include "enemyState.h"

class EnemyFlying: public EnemyState {
private:
    float timeToFly;
    float timeMoved = -1;

public:
    explicit EnemyFlying(float time);
    std::unique_ptr<EnemyState> update(float time) override;
    std::unique_ptr<EnemyState> attackCharacter(std::shared_ptr<Character> character, int16_t dmg,
                                                float time) override;
    std::unique_ptr<EnemyState> receivingDmg(float time) override;
    std::unique_ptr<EnemyState> die(float time) override;
    void setVelocity(float vel) override;
};

#endif  // ENEMY_FLYING_H
