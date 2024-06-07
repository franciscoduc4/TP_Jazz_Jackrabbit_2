#include "jazz.h"

#define CONFIG ServerConfig::getInstance()

Jazz::Jazz(GameMap& map, Vector<int16_t> pos, int16_t characterId):
        Character(map, pos, characterId, CharacterType::JAZZ, CONFIG->getJazzSpeed(),
                  CONFIG->getJazzSprintSpeed(), CONFIG->getJazzJumpHeight(),
                  CONFIG->getJazzShootCooldownTime()) {}

void Jazz::specialAttack(float time) {
    // Implement Jazz's special attack logic here
}
