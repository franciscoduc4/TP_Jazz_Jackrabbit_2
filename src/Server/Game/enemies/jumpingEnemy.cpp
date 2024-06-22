#include "jumpingEnemy.h"

// #define CONFIG ServerConfig::getInstance()

JumpingEnemy::JumpingEnemy(GameMap& map, Vector<uint32_t> pos, uint8_t id, uint32_t width, uint32_t height):
        Enemy(map, pos, id, ServerConfig::getJumpingEnemyInitialHealth(), Direction::LEFT,
              ServerConfig::getJumpingEnemyDamage(), std::make_unique<EnemyIdle>(),
              ServerConfig::getJumpingEnemyViewDistance(), ServerConfig::getJumpingEnemyViewDistanceHit(),
              ServerConfig::getJumpingEnemyMaxMovesPerCell(), ServerConfig::getJumpingEnemyHitDistance(), {},
              ServerConfig::getJumpingEnemyJumpProb(), {},
              width, height) {}


EnemyType JumpingEnemy::getEnemyType() const { return EnemyType::SCHWARZENGUARD; }

void JumpingEnemy::update(double deltaTime) {
}
