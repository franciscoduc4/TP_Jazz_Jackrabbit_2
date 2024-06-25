#include "spaz.h"

// #define CONFIG ServerConfig::getInstance()

Spaz::Spaz(GameMap& map, Vector<uint32_t> pos, uint8_t playerId, uint32_t width, uint32_t height):
        Character(map, pos, playerId, CharacterType::SPAZ, ServerConfig::getSpazHorizontalSpeed(),
                  ServerConfig::getSpazSprintSpeed(), ServerConfig::getSpazVerticalSpeed(),
                  ServerConfig::getSpazJumpHeight(), ServerConfig::getSpazShootCooldownTime(), width,
                  height) {}

void Spaz::specialAttack(float time) {
}
void Spaz::update(double deltaTime) {
}
