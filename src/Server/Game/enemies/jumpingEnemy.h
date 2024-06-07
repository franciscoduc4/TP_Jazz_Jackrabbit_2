#ifndef JUMPING_ENEMY_H
#define JUMPING_ENEMY_H

#include <memory>
#include <vector>

#include "../../../Common/Config/ServerConfig.h"
#include "../gameMap.h"
#include "states/enemyIdle.h"
#include "states/enemyState.h"

#include "enemy.h"

class JumpingEnemy: public Enemy {
private:
    GameMap& map;

public:
    JumpingEnemy(Vector<int16_t> pos, int16_t id, GameMap& map, int16_t health, uint16_t dmg);

    EnemyType getEnemyType() override;
};

#endif  // JUMPING_ENEMY_H
