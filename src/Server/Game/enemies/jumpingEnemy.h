#ifndef JUMPING_ENEMY_H
#define JUMPING_ENEMY_H

#include <memory>
#include <vector>

#include "../../../Common/Config/ServerConfig.h"
#include "states/enemyIdle.h"
#include "states/enemyState.h"

#include "enemy.h"

class JumpingEnemy: public Enemy {

public:
    JumpingEnemy(GameMap& map, Vector<uint8_t> pos, uint8_t id);

    EnemyType getEnemyType() override;
};

#endif  // JUMPING_ENEMY_H
