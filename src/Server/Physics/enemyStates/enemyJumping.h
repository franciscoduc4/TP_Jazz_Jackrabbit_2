#ifndef ENEMY_JUMPING_H
#define ENEMY_JUMPING_H

#include <memory>

#include "enemyState.h"

class EnemyJumping: public EnemyState {
private:
    float timeToJump;
    float timeJumped = -1;

public:
    explicit EnemyJumping(float time);
    std::unique_ptr<EnemyState> update(float time) override;
    std::unique_ptr<EnemyState> attackCharacter(std::shared_ptr<Character> character, int16_t dmg,
                                                float time) override;
    std::unique_ptr<EnemyState> receivingDmg(float time) override;
    std::unique_ptr<EnemyState> die(float time) override;
    void setVelocity(float vel) override;
};

#endif  // ENEMY_JUMPING_H
