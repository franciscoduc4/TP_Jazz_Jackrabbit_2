#include "walkingEnemy.h"

#define CONFIG ServerConfig::getInstance()

WalkingEnemy::WalkingEnemy(Vector<int16_t> pos, int16_t id, GameMap& map, int16_t health,
                           uint16_t dmg):
        map(map),
        Enemy(pos, id, health, Direction::LEFT, dmg, std::make_unique<EnemyIdle>(),
              CONFIG->getWalkingEnemyViewDistance(), CONFIG->getWalkingEnemyViewDistanceHit(),
              CONFIG->getWalkingEnemyMaxMovesPerCell(), CONFIG->getWalkingEnemyHitDistance(),
              CONFIG->getWalkingEnemyWalkProb(), {}, {}) {}


EnemyType WalkingEnemy::getEnemyType() { return EnemyType::WALKING_ENEMY; }