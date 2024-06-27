#include "Schwarzenguard.h"

// #define CONFIG ServerConfig::getInstance()

Schwarzenguard::Schwarzenguard(GameMap& map, Vector<uint32_t> pos, uint8_t id, uint32_t width, uint32_t height):
        Enemy(map, pos, id, ServerConfig::getSchwarzenguardEnemyInitialHealth(), Direction::LEFT,
              ServerConfig::getSchwarzenguardEnemyDamage(), std::make_unique<EnemyIdle>(),
              ServerConfig::getSchwarzenguardEnemyViewDistance(), ServerConfig::getSchwarzenguardEnemyViewDistanceHit(),
              ServerConfig::getSchwarzenguardEnemyMaxMovesPerCell(), ServerConfig::getSchwarzenguardEnemyHitDistance(), {},
              ServerConfig::getSchwarzenguardEnemyJumpProb(), {},
              width, height) {}


EnemyType Schwarzenguard::getEnemyType() const { return EnemyType::SCHWARZENGUARD; }

void Schwarzenguard::update(double deltaTime) {
}

