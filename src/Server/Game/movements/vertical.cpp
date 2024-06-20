#include "vertical.h"

VerticalMovement::VerticalMovement(float strength):
        speed(0), strength(strength), gravity(ServerConfig::getGameGravity()) {
    std::cout << "[VERTICAL MOVEMENT] Init strength: " << strength << " gravity: " << gravity
              << std::endl;
}

void VerticalMovement::jump(std::shared_ptr<Terrain> terrain) {
    speed = terrain->applyVerticalFriction(strength);
    speed += terrain->getVerticalAcceleration(strength);
}

void VerticalMovement::move(std::shared_ptr<Position> position) {
    uint32_t speedY = this->speed * 0.16;
    position->moveY(speedY);
    applyGravity();
}

void VerticalMovement::applyGravity() { this->speed += this->gravity * 0.16; }

float VerticalMovement::getSpeed() { return this->speed; }

void VerticalMovement::setSpeed(float speed) { this->speed = speed; }