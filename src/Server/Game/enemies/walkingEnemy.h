#ifndef WALKING_ENEMY_H
#define WALKING_ENEMY_H

#include <memory>
#include <vector>

#include "../../../Common/Config/ServerConfig.h"
#include "states/enemyIdle.h"
#include "states/enemyState.h"

#include "enemy.h"

class WalkingEnemy: public Enemy {

public:
    WalkingEnemy(GameMap& map, Vector<uint8_t> pos, uint8_t id);

    EnemyType getEnemyType() override;
};

#endif  // WALKING_ENEMY_H