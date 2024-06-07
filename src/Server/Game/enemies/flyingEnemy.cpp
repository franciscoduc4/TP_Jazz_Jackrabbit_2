#include "flyingEnemy.h"

#define CONFIG ServerConfig::getInstance()

FlyingEnemy::FlyingEnemy(Vector<int16_t> pos, int16_t id, GameMap& map, int16_t health,
                         uint16_t dmg):
        map(map),
        Enemy(pos, id, health, Direction::LEFT, dmg, std::make_unique<EnemyIdle>(),
              CONFIG->getFlyingEnemyViewDistance(), CONFIG->getFlyingEnemyViewDistanceHit(),
              CONFIG->getFlyingEnemyMaxMovesPerCell(), CONFIG->getFlyingEnemyHitDistance(), {}, {},
              CONFIG->getFlyingEnemyFlyProb()) {}


EnemyType FlyingEnemy::getEnemyType() { return EnemyType::FLYING_ENEMY; }
