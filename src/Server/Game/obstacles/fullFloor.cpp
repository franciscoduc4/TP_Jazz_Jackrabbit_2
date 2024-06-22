#include "fullFloor.h"

FullFloor::FullFloor(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height)
    : Obstacle(gameMap, position,  width,  height) {}

void FullFloor::update(double deltaTime) {
    // Implementar lógica específica para FullFloor
}
