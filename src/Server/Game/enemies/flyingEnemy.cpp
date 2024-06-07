#include "flyingEnemy.h"

#define CONFIG ServerConfig::getInstance()

FlyingEnemy::FlyingEnemy(GameMap& map, Vector<int16_t> pos, int16_t id):
        map(map),
        Enemy(pos, id, CONFIG->getFlyingEnemyInitialHealth(), Direction::LEFT,
              CONFIG->getFlyingEnemyDamage(), std::make_unique<EnemyIdle>(),
              CONFIG->getFlyingEnemyViewDistance(), CONFIG->getFlyingEnemyViewDistanceHit(),
              CONFIG->getFlyingEnemyMaxMovesPerCell(), CONFIG->getFlyingEnemyHitDistance(), {}, {},
              CONFIG->getFlyingEnemyFlyProb()) {}


EnemyType FlyingEnemy::getEnemyType() { return EnemyType::FLYING_ENEMY; }
