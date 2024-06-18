#include "jazz.h"

// #define CONFIG ServerConfig::getInstance()

Jazz::Jazz(GameMap& map, Vector<uint8_t> pos, uint8_t playerId):
        Character(map, pos, playerId, CharacterType::JAZZ, ServerConfig::getJazzHorizontalSpeed(),
                  ServerConfig::getJazzSprintSpeed(), ServerConfig::getJazzVerticalSpeed(),
                  ServerConfig::getJazzJumpHeight(), ServerConfig::getJazzShootCooldownTime()) {}

void Jazz::specialAttack(float time) {
    // Implement Jazz's special attack logic here
}
