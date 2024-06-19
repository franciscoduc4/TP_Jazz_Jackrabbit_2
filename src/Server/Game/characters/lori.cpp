#include "lori.h"

// #define CONFIG ServerConfig::getInstance()

Lori::Lori(GameMap& map, Vector<uint32_t> pos, uint8_t playerId):
        Character(map, pos, playerId, CharacterType::LORI, ServerConfig::getLoriHorizontalSpeed(),
                  ServerConfig::getLoriSprintSpeed(), ServerConfig::getLoriVerticalSpeed(),
                  ServerConfig::getLoriJumpHeight(), ServerConfig::getLoriShootCooldownTime()) {}

void Lori::specialAttack(float time) {
    // Implement Lori's special attack logic here
}
