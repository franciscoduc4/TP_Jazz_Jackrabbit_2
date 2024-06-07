#ifndef JUMPING_ENEMY_H
#define JUMPING_ENEMY_H

#include <memory>
#include <vector>

#include "../../../Common/Config/ServerConfig.h"
#include "states/enemyIdle.h"
#include "states/enemyState.h"

#include "enemy.h"

class GameMap;

class JumpingEnemy: public Enemy {
private:
    GameMap& map;

public:
    JumpingEnemy(GameMap& map, Vector<int16_t> pos, int16_t id);

    EnemyType getEnemyType() override;
};

#endif  // JUMPING_ENEMY_H
