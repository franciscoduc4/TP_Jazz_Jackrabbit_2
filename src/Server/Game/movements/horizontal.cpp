#include "horizontal.h"

#include "../terrains/terrain.h"

HorizontalMovement::HorizontalMovement(float maxSpeed, float acceleration):
        speed(0), maxSpeed(maxSpeed), acceleration(acceleration) {
    std::cout << "[HORIZONTAL MOVEMENT] Init maxSpeed: " << maxSpeed
              << " acceleration: " << acceleration << std::endl;
}


void HorizontalMovement::accelerateLeft(std::shared_ptr<Terrain> terrain) {
    uint32_t deltaSpeed = terrain->getHorizontalAcceleration(acceleration);
    if (speed < -maxSpeed) {
        speed = -maxSpeed;
    } else {
        speed -= deltaSpeed;
    }
}

void HorizontalMovement::accelerateRight(std::shared_ptr<Terrain> terrain) {
    uint32_t deltaSpeed = terrain->getHorizontalAcceleration(acceleration);
    if (speed > maxSpeed) {
        speed = maxSpeed;
    } else {
        speed += deltaSpeed;
    }
}

void HorizontalMovement::move(std::shared_ptr<Position> position,
                              std::shared_ptr<Terrain> terrain) {
    position->moveX(speed);
    speed = terrain->applyHorizontalFriction(speed);
}

float HorizontalMovement::getSpeed() { return this->speed; }

void HorizontalMovement::setSpeed(float speed) { this->speed = speed; }