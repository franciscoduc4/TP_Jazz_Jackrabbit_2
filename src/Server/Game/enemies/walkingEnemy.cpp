#include "walkingEnemy.h"

#define CONFIG ServerConfig::getInstance()

WalkingEnemy::WalkingEnemy(GameMap& map, Vector<int16_t> pos, int16_t id):
        map(map),
        Enemy(pos, id, CONFIG->getWalkingEnemyInitialHealth(), Direction::LEFT,
              CONFIG->getWalkingEnemyDamage(), std::make_unique<EnemyIdle>(),
              CONFIG->getWalkingEnemyViewDistance(), CONFIG->getWalkingEnemyViewDistanceHit(),
              CONFIG->getWalkingEnemyMaxMovesPerCell(), CONFIG->getWalkingEnemyHitDistance(),
              CONFIG->getWalkingEnemyWalkProb(), {}, {}) {}


EnemyType WalkingEnemy::getEnemyType() { return EnemyType::WALKING_ENEMY; }