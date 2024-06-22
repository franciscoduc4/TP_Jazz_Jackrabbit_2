
#include "obstacle.h"

Obstacle::Obstacle(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height)
    : Entity(position, 0, 1, Direction::UP, EntityType::OBSTACLE), position(position) {}

void Obstacle::update(double deltaTime) {
    // Do nothing
}

TileDTO Obstacle::getDTO() {
    
    return TileDTO{position.x, position.y, getObstacleType()};
}