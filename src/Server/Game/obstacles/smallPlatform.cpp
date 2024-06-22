#include "smallPlatform.h"

SmallPlatform::SmallPlatform(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height)
    : Obstacle(gameMap, position,  width,  height) {}

void SmallPlatform::update(double deltaTime) {
    // Implementar lógica específica para SmallPlatform
}
