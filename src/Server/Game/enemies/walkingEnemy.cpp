#include "walkingEnemy.h"

#define CONFIG ServerConfig::getInstance()

WalkingEnemy::WalkingEnemy(GameMap& map, Vector<uint8_t> pos, uint8_t id):
        Enemy(map, pos, id, CONFIG->getWalkingEnemyInitialHealth(), Direction::LEFT,
              CONFIG->getWalkingEnemyDamage(), std::make_unique<EnemyIdle>(),
              CONFIG->getWalkingEnemyViewDistance(), CONFIG->getWalkingEnemyViewDistanceHit(),
              CONFIG->getWalkingEnemyMaxMovesPerCell(), CONFIG->getWalkingEnemyHitDistance(),
              CONFIG->getWalkingEnemyWalkProb(), {}, {}) {}


EnemyType WalkingEnemy::getEnemyType() { return EnemyType::TURTLE; }