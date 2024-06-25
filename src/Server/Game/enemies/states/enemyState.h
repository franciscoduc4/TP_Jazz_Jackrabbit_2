#ifndef ENEMY_STATE_H
#define ENEMY_STATE_H

#include <iostream>
#include <memory>

#include "../../../../Common/Types/entity.h"
#include "../../characters/character.h"

class Character;

class EnemyState {
public:
    EnemyStateEntity enemyState = ENEMY_IDLE;

    virtual std::unique_ptr<EnemyState> update(float time) = 0;
    virtual std::unique_ptr<EnemyState> attackCharacter(std::shared_ptr<Character> character,
                                                        int16_t dmg, float time) = 0;
    virtual std::unique_ptr<EnemyState> receivingDmg(float time) = 0;
    virtual std::unique_ptr<EnemyState> die(float time) = 0;
    virtual void setVelocity(float vel) = 0;

    EnemyStateEntity getState(){ return enemyState; }

    virtual ~EnemyState() = default;
};

#endif  // ENEMY_STATE_H
