#include "jumpingEnemy.h"

#define CONFIG ServerConfig::getInstance()

JumpingEnemy::JumpingEnemy(GameMap& map, Vector<uint8_t> pos, uint8_t id):
        Enemy(map, pos, id, CONFIG->getJumpingEnemyInitialHealth(), Direction::LEFT,
              CONFIG->getJumpingEnemyDamage(), std::make_unique<EnemyIdle>(),
              CONFIG->getJumpingEnemyViewDistance(), CONFIG->getJumpingEnemyViewDistanceHit(),
              CONFIG->getJumpingEnemyMaxMovesPerCell(), CONFIG->getJumpingEnemyHitDistance(), {},
              CONFIG->getJumpingEnemyJumpProb(), {}) {}


EnemyType JumpingEnemy::getEnemyType() { return EnemyType::SCHWARZENGUARD; }
