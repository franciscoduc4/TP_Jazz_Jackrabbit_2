#include "lori.h"

#define CONFIG ServerConfig::getInstance()

Lori::Lori(GameMap& map, Vector<int16_t> pos, int16_t characterId):
        Character(map, pos, characterId, CharacterType::LORI, CONFIG->getLoriHorizontalSpeed(),
                  CONFIG->getLoriSprintSpeed(), CONFIG->getLoriVerticalSpeed(),
                  CONFIG->getLoriJumpHeight(), CONFIG->getLoriShootCooldownTime()) {}

void Lori::specialAttack(float time) {
    // Implement Lori's special attack logic here
}
