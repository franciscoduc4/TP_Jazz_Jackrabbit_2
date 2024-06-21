#ifndef FLYING_ENEMY_H
#define FLYING_ENEMY_H

#include <memory>
#include <vector>

#include "../../../Common/Config/ServerConfig.h"
#include "states/enemyIdle.h"
#include "states/enemyState.h"

#include "enemy.h"

class FlyingEnemy: public Enemy {

public:
    FlyingEnemy(GameMap& map, Vector<uint32_t> pos, uint8_t id);

    EnemyType getEnemyType() const override;

    void update(double deltaTime) override;
};

#endif  // FLYING_ENEMY_H
