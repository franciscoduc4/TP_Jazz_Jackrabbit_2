#ifndef FLYING_ENEMY_H
#define FLYING_ENEMY_H

#include <memory>
#include <vector>

#include "../../../Common/Config/ServerConfig.h"
#include "states/enemyIdle.h"
#include "states/enemyState.h"

#include "enemy.h"

class GameMap;

class FlyingEnemy: public Enemy {
private:
    GameMap& map;

public:
    FlyingEnemy(GameMap& map, Vector<int16_t> pos, int16_t id);

    EnemyType getEnemyType() override;
};

#endif  // FLYING_ENEMY_H
