#include "walkingEnemy.h"

// #define CONFIG ServerConfig::getInstance()

WalkingEnemy::WalkingEnemy(GameMap& map, Vector<uint32_t> pos, uint8_t id):
        Enemy(map, pos, id, ServerConfig::getWalkingEnemyInitialHealth(), Direction::LEFT,
              ServerConfig::getWalkingEnemyDamage(), std::make_unique<EnemyIdle>(),
              ServerConfig::getWalkingEnemyViewDistance(), ServerConfig::getWalkingEnemyViewDistanceHit(),
              ServerConfig::getWalkingEnemyMaxMovesPerCell(), ServerConfig::getWalkingEnemyHitDistance(),
              ServerConfig::getWalkingEnemyWalkProb(), {}, {}) {}


EnemyType WalkingEnemy::getEnemyType() const { return EnemyType::TURTLE; }

void WalkingEnemy::update(double deltaTime) {
}



