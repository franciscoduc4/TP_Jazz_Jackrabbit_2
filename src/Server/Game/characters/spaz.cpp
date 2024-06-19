#include "spaz.h"

#define CONFIG ServerConfig::getInstance()

Spaz::Spaz(GameMap& map, Vector<uint8_t> pos, uint8_t playerId):
        Character(map, pos, playerId, CharacterType::SPAZ, CONFIG->getSpazHorizontalSpeed(),
                  CONFIG->getSpazSprintSpeed(), CONFIG->getSpazVerticalSpeed(),
                  CONFIG->getSpazJumpHeight(), CONFIG->getSpazShootCooldownTime()) {}

void Spaz::specialAttack(float time) {
    // Implement Spaz's special attack logic here
}
