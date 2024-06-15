#include "lori.h"

#define CONFIG ServerConfig::getInstance()

Lori::Lori(GameMap& map, Vector<uint8_t> pos, uint8_t playerId):
        Character(map, pos, playerId, CharacterType::LORI, CONFIG->getLoriHorizontalSpeed(),
                  CONFIG->getLoriSprintSpeed(), CONFIG->getLoriVerticalSpeed(),
                  CONFIG->getLoriJumpHeight(), CONFIG->getLoriShootCooldownTime()) {}

void Lori::specialAttack(float time) {
    // Implement Lori's special attack logic here
}
