#include "jumpingEnemy.h"

// #define CONFIG ServerConfig::getInstance()

JumpingEnemy::JumpingEnemy(GameMap& map, Vector<uint8_t> pos, uint8_t id):
        Enemy(map, pos, id, ServerConfig::getJumpingEnemyInitialHealth(), Direction::LEFT,
              ServerConfig::getJumpingEnemyDamage(), std::make_unique<EnemyIdle>(),
              ServerConfig::getJumpingEnemyViewDistance(), ServerConfig::getJumpingEnemyViewDistanceHit(),
              ServerConfig::getJumpingEnemyMaxMovesPerCell(), ServerConfig::getJumpingEnemyHitDistance(), {},
              ServerConfig::getJumpingEnemyJumpProb(), {}) {}


EnemyType JumpingEnemy::getEnemyType() { return EnemyType::SCHWARZENGUARD; }
