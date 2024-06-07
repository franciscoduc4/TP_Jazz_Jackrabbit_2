#include "jumpingEnemy.h"

#define CONFIG ServerConfig::getInstance()

JumpingEnemy::JumpingEnemy(Vector<int16_t> pos, int16_t id, GameMap& map, int16_t health,
                           uint16_t dmg):
        map(map),
        Enemy(pos, id, health, Direction::LEFT, dmg, std::make_unique<EnemyIdle>(),
              CONFIG->getJumpingEnemyViewDistance(), CONFIG->getJumpingEnemyViewDistanceHit(),
              CONFIG->getJumpingEnemyMaxMovesPerCell(), CONFIG->getJumpingEnemyHitDistance(), {},
              CONFIG->getJumpingEnemyJumpProb(), {}) {}


EnemyType JumpingEnemy::getEnemyType() { return EnemyType::JUMPING_ENEMY; }
