#include "spaz.h"

// #define CONFIG ServerConfig::getInstance()

Spaz::Spaz(GameMap& map, Vector<uint32_t> pos, uint8_t playerId):
        Character(map, pos, playerId, CharacterType::SPAZ, ServerConfig::getSpazHorizontalSpeed(),
                  ServerConfig::getSpazSprintSpeed(), ServerConfig::getSpazVerticalSpeed(),
                  ServerConfig::getSpazJumpHeight(), ServerConfig::getSpazShootCooldownTime()) {}

void Spaz::specialAttack(float time) {
    // Implement Spaz's special attack logic here
}
void Spaz::update(double deltaTime) {
}
