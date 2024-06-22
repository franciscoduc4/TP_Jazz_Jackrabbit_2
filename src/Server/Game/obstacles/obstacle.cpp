
#include "obstacle.h"

Obstacle::Obstacle(GameMap& gameMap, Vector<uint32_t> position)
    : Entity(position, 0, 1, Direction::UP, EntityType::OBSTACLE), position(position) {}

void Obstacle::update(double deltaTime) {
    // Do nothing
}

TileDTO Obstacle::getDTO() {
    
    return TileDTO{position.x, position.y, getObstacleType()};
}