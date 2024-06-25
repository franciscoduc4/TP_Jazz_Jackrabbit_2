#include "lori.h"

// #define CONFIG ServerConfig::getInstance()

Lori::Lori(GameMap& map, Vector<uint32_t> pos, uint8_t playerId, uint32_t width, uint32_t height):
        Character(map, pos, playerId, CharacterType::LORI, ServerConfig::getLoriHorizontalSpeed(),
                  ServerConfig::getLoriSprintSpeed(), ServerConfig::getLoriVerticalSpeed(),
                  ServerConfig::getLoriJumpHeight(), ServerConfig::getLoriShootCooldownTime(),
                  width, height) {}

void Lori::specialAttack(float time) {
    // Implement Lori's special attack logic here
}

void Lori::update(double deltaTime) {
}
