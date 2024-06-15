#include "jazz.h"

#define CONFIG ServerConfig::getInstance()

Jazz::Jazz(GameMap& map, Vector<uint8_t> pos, uint8_t playerId):
        Character(map, pos, playerId, CharacterType::JAZZ, CONFIG->getJazzHorizontalSpeed(),
                  CONFIG->getJazzSprintSpeed(), CONFIG->getJazzVerticalSpeed(),
                  CONFIG->getJazzJumpHeight(), CONFIG->getJazzShootCooldownTime()) {}

void Jazz::specialAttack(float time) {
    // Implement Jazz's special attack logic here
}
