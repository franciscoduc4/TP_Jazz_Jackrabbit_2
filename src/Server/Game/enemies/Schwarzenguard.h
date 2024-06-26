#ifndef SCHWARZENGUARD_H
#define SCHWARZENGUARD_H

#include <memory>
#include <vector>

#include "../../../Common/Config/ServerConfig.h"
#include "states/enemyIdle.h"
#include "states/enemyState.h"

#include "enemy.h"

class Schwarzenguard: public Enemy {

public:
    Schwarzenguard(GameMap& map, Vector<uint32_t> pos, uint8_t id, uint32_t width, uint32_t height);

    EnemyType getEnemyType() const override;

    void update(double deltaTime) override;

    uint8_t getDamage() const override { return ServerConfig::getJumpingEnemyDamage(); }

    uint32_t getWidth() const override { return ServerConfig::getJumpingEnemyWidth(); }
    uint32_t getHeight() const override { return ServerConfig::getJumpingEnemyHeight(); }

    
};

#endif  // SCHWARZENGUARD_H
