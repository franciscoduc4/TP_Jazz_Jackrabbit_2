#include "Turtle.h"

// #define CONFIG ServerConfig::getInstance()


Turtle::Turtle(GameMap& map, Vector<uint32_t> pos, uint8_t id, uint32_t width, uint32_t height):
        Enemy(map, pos, id, ServerConfig::getWalkingEnemyInitialHealth(), Direction::LEFT,
              ServerConfig::getWalkingEnemyDamage(), std::make_unique<EnemyIdle>(),
              ServerConfig::getWalkingEnemyViewDistance(), ServerConfig::getWalkingEnemyViewDistanceHit(),
              ServerConfig::getWalkingEnemyMaxMovesPerCell(), ServerConfig::getWalkingEnemyHitDistance(),
              ServerConfig::getWalkingEnemyWalkProb(), {}, {},
              width,
              height) {}


EnemyType Turtle::getEnemyType() const { return EnemyType::TURTLE; }

void Turtle::update(double deltaTime) {
}



