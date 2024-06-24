#include "Yellowmon.h"

// #define CONFIG ServerConfig::getInstance()

Yellowmon::Yellowmon(GameMap& map, Vector<uint32_t> pos, uint8_t id, uint32_t width, uint32_t height):
        Enemy(map, pos, id, ServerConfig::getFlyingEnemyInitialHealth(), Direction::LEFT,
              ServerConfig::getFlyingEnemyDamage(), std::make_unique<EnemyIdle>(),
              ServerConfig::getFlyingEnemyViewDistance(), ServerConfig::getFlyingEnemyViewDistanceHit(),
              ServerConfig::getFlyingEnemyMaxMovesPerCell(), ServerConfig::getFlyingEnemyHitDistance(), {}, {},
              ServerConfig::getFlyingEnemyFlyProb(),
              width,
              height) {}


EnemyType Yellowmon::getEnemyType() const { return EnemyType::YELLOWMON; }
void Yellowmon::update(double deltaTime) {
}
