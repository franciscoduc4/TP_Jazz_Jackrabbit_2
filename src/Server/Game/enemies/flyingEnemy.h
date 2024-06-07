#ifndef FLYING_ENEMY_H
#define FLYING_ENEMY_H

#include <memory>
#include <vector>

#include "../../../Common/Config/ServerConfig.h"
#include "../gameMap.h"
#include "states/enemyIdle.h"
#include "states/enemyState.h"

#include "enemy.h"

class FlyingEnemy: public Enemy {
private:
    GameMap& map;

public:
    FlyingEnemy(Vector<int16_t> pos, int16_t id, GameMap& map, int16_t health, uint16_t dmg);

    EnemyType getEnemyType() override;
};

#endif  // FLYING_ENEMY_H
