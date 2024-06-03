#ifndef ENEMY_RECEIVING_DMG_H
#define ENEMY_RECEIVING_DMG_H

#include <memory>

#include "enemyState.h"

class EnemyReceivingDmg: public EnemyState {
private:
    float startTime;
    float timeReceivedDmg;

public:
    explicit EnemyReceivingDmg(float time);
    std::unique_ptr<EnemyState> update(float time) override;
    std::unique_ptr<EnemyState> attackCharacter(std::shared_ptr<Character> character, int16_t dmg,
                                                float time) override;
    std::unique_ptr<EnemyState> receivingDmg(float time) override;
    std::unique_ptr<EnemyState> die(float time) override;
    void setVelocity(float vel) override;
};

#endif  // ENEMY_RECEIVING_DMG_H
