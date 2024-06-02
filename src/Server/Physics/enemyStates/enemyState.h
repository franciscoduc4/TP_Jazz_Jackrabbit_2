#ifndef ENEMY_STATE_H
#define ENEMY_STATE_H

#include <memory>
#include <iostream>
#include "../../../Common/Types/entity.h"

class Character;
class Enemy;
class GameMap;

class EnemyState {
public:
    EnemyStateEntity enemyState = ENEMY_IDLE;

    virtual std::unique_ptr<EnemyState> update(float time) = 0;
    virtual std::unique_ptr<EnemyState> attackCharacter(Character* character, 
    int16_t dmg, float time) = 0;
    virtual std::unique_ptr<EnemyState> receivingDmg(float time) = 0;
    virtual std::unique_ptr<EnemyState> die(float time) = 0;
    virtual void setVelocity(float vel) = 0;

    virtual ~EnemyState() = default; 
};

#endif // ENEMY_STATE_H
