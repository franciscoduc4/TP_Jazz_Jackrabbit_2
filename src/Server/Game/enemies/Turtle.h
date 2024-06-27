#ifndef TURTLE_H
#define TURTLE_H

#include <memory>
#include <vector>

#include "../../../Common/Config/ServerConfig.h"
#include "states/enemyIdle.h"
#include "states/enemyState.h"

#include "enemy.h"

class Turtle: public Enemy {

public:
    Turtle(GameMap& map, Vector<uint32_t> pos, uint8_t id, uint32_t width, uint32_t height);

    EnemyType getEnemyType() const override { return EnemyType::TURTLE; }

    void update(double deltaTime) override;

    uint8_t getDamage() const override { return ServerConfig::getTurtleEnemyDamage(); }

    uint32_t getWidth() const override { return ServerConfig::getTurtleEnemyWidth(); }
    uint32_t getHeight() const override { return ServerConfig::getTurtleEnemyHeight(); }

    uint32_t getPointsValue() const override { return ServerConfig::getTurtleEnemyValue(); }

    
};

#endif  // TURTLE_H