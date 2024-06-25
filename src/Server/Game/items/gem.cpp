#include "gem.h"

Gem::Gem(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height)
    : Item(gameMap, position, width, height) {}

void Gem::update(double deltaTime) {
    // Implementar lógica específica para Gem
}
