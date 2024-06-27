#include "Turtle.h"

// #define CONFIG ServerConfig::getInstance()


Turtle::Turtle(GameMap& map, Vector<uint32_t> pos, uint8_t id, uint32_t width, uint32_t height):
        Enemy(map, pos, id, ServerConfig::getTurtleEnemyInitialHealth(), Direction::LEFT,
              ServerConfig::getTurtleEnemyDamage(), std::make_unique<EnemyIdle>(),
              ServerConfig::getTurtleEnemyViewDistance(), ServerConfig::getTurtleEnemyViewDistanceHit(),
              ServerConfig::getTurtleEnemyMaxMovesPerCell(), ServerConfig::getTurtleEnemyHitDistance(),
              ServerConfig::getTurtleEnemyWalkProb(), {}, {},
              width,
              height) {}


//EnemyType Turtle::getEnemyType() const { return EnemyType::TURTLE; }

void Turtle::update(double deltaTime) {
}



