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
    FlyingEnemy(GameMap& map, Vector<uint32_t> pos, uint8_t id, uint32_t width, uint32_t height);

    EnemyType getEnemyType() const override;

    void update(double deltaTime) override;

    uint8_t getDamage() const override { return ServerConfig::getFlyingEnemyDamage(); }

    uint32_t getWidth() const { return 25; }
    uint32_t getHeight() const { return 70; }
};

#endif  // FLYING_ENEMY_H
