#include "spaz.h"

#define CONFIG ServerConfig::getInstance()

Spaz::Spaz(GameMap& map, Vector<int16_t> pos, int16_t characterId):
        Character(map, pos, characterId, CharacterType::SPAZ, CONFIG->getSpazHorizontalSpeed(),
                  CONFIG->getSpazSprintSpeed(), CONFIG->getSpazVerticalSpeed(),
                  CONFIG->getSpazJumpHeight(), CONFIG->getSpazShootCooldownTime()) {}

void Spaz::specialAttack(float time) {
    // Implement Spaz's special attack logic here
}
