#ifndef YELLOWMON_H
#define YELLOWMON_H

#include <memory>
#include <vector>

#include "../../../Common/Config/ServerConfig.h"
#include "states/enemyIdle.h"
#include "states/enemyState.h"

#include "enemy.h"

class Yellowmon: public Enemy {

public:
    Yellowmon(GameMap& map, Vector<uint32_t> pos, uint8_t id, uint32_t width, uint32_t height);

    EnemyType getEnemyType() const override;

    void update(double deltaTime) override;

    uint8_t getDamage() const override { return ServerConfig::getYellowmonsEnemyDamage(); }

    uint32_t getWidth() const override { return ServerConfig::getYellowmonsEnemyWidth(); }
    uint32_t getHeight() const override { return ServerConfig::getYellowmonsEnemyHeight(); }

    uint32_t getPointsValue() const override { return ServerConfig::getYellowmonsEnemyValue(); }

};

#endif  // YELLOWMON_H
