#ifndef WALKING_ENEMY_H
#define WALKING_ENEMY_H

#include <memory>
#include <vector>

#include "../../../Common/Config/ServerConfig.h"
#include "states/enemyIdle.h"
#include "states/enemyState.h"

#include "enemy.h"

class GameMap;

class WalkingEnemy: public Enemy {
private:
    GameMap& map;

public:
    WalkingEnemy(GameMap& map, Vector<int16_t> pos, int16_t id);

    EnemyType getEnemyType() override;
};

#endif  // WALKING_ENEMY_H