#include "movement.h"

#include "../terrains/air.h"

Movement::Movement():
        horizontalMovement(ServerConfig::getCharacterSpeed(),
                           ServerConfig::getCharacterAcceleration()),
        verticalMovement(ServerConfig::getCharacterJumpStrength()) {
    terrains.emplace(TerrainType::AIR, std::make_shared<Air>());
    currentTerrain = TerrainType::AIR;
}

void Movement::accelerate(Direction direction) {
    switch (direction) {
        case Direction::LEFT:
            this->horizontalMovement.accelerateLeft(terrains[currentTerrain]);
            break;
        case Direction::RIGHT:
            this->horizontalMovement.accelerateRight(terrains[currentTerrain]);
            break;
        case Direction::UP:
            this->verticalMovement.jump(terrains[currentTerrain]);
            currentTerrain = TerrainType::AIR;
            break;
        default:
            break;
    }
}

void Movement::move(std::shared_ptr<Position> position) {
    this->horizontalMovement.move(position, terrains[currentTerrain]);
    this->verticalMovement.move(position);
}

float Movement::getHorizontalSpeed() { return this->horizontalMovement.getSpeed(); }

float Movement::getVerticalSpeed() { return this->verticalMovement.getSpeed(); }

void Movement::setHorizontalSpeed(float speed) { this->horizontalMovement.setSpeed(speed); }

void Movement::setVerticalSpeed(float speed) { this->verticalMovement.setSpeed(speed); }
