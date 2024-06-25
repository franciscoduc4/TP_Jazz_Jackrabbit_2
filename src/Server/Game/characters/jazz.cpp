#include "jazz.h"

// #define CONFIG ServerConfig::getInstance()

Jazz::Jazz(GameMap& map, Vector<uint32_t> pos, uint8_t playerId, uint32_t width, uint32_t height):
        Character(map, pos, playerId, CharacterType::JAZZ, ServerConfig::getJazzHorizontalSpeed(),
                  ServerConfig::getJazzSprintSpeed(), ServerConfig::getJazzVerticalSpeed(),
                  ServerConfig::getJazzJumpHeight(), ServerConfig::getJazzShootCooldownTime(), width,
                  height) {}

void Jazz::specialAttack(float time) {
    // Implement Jazz's special attack logic here
}

void Jazz::update(double deltaTime) {
}
