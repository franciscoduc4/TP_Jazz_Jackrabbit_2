#ifndef ENEMY_WALKING_H
#define ENEMY_WALKING_H

#include "enemyState.h"
#include <memory>

class EnemyWalking : public EnemyState {
    private:
        float timeToWalk;
        float timeMoved = -1;

    public:
        explicit EnemyWalking(float time);
        std::unique_ptr<EnemyState> update(float time) override;
        std::unique_ptr<EnemyState> attackCharacter(Character* character, 
        int16_t dmg, float time) override;
        std::unique_ptr<EnemyState> receivingDmg(float time) override;
        std::unique_ptr<EnemyState> die(float time) override;
        void setVelocity(float vel) override;
        
};

#endif 
