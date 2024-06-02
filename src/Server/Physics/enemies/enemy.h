#ifndef ENEMY_H_
#define ENEMY_H_

#include <iostream>
#include <memory>
#include <vector>

#include "../../../Common/Types/enemy.h"
#include "../enemyStates/enemyState.h"
#include "../entity.h"


class Enemy: public Entity {
public:
    virtual void update(std::vector<Character*> characters, float time) = 0;
    virtual void setDir(int16_t dir) = 0;
    virtual void receiveDmg(int16_t dmg, float time) = 0;
    virtual void attack(std::vector<Character*> characters, float time) = 0;
    virtual void die(float time) = 0;
    virtual std::unique_ptr<EnemyState>& getState() = 0;
    virtual int16_t getMatrixX() = 0;
    virtual int16_t getMatrixY() = 0;
    virtual int16_t getX() = 0;
    virtual int16_t getY() = 0;
    virtual int16_t getHealth() = 0;
    virtual EnemyType getEnemyType() = 0;
    virtual ~Enemy() = default;
};

#endif  // ENEMY_H_
