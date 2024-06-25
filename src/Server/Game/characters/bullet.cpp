#include "bullet.h"

Bullet::Bullet(Vector<uint32_t> pos, Direction dir, uint32_t damage, uint32_t speed, uint8_t shooterId)
    : Entity(pos, 0, 1, dir, EntityType::BULLET), dir(dir), damage(damage), speed(speed),  shooterId(shooterId), alive(true) {
}

void Bullet::update(double deltaTime) {
    // Update bullet position based on its speed and direction
    switch (dir) {
    case Direction::LEFT:
        pos.x -= static_cast<uint32_t>(speed * deltaTime);
        break;
    case Direction::RIGHT:
        pos.x += static_cast<uint32_t>(speed * deltaTime);
        break;
    case Direction::UP:
        pos.y -= static_cast<uint32_t>(speed * deltaTime);
        break;
    case Direction::DOWN:
        pos.y += static_cast<uint32_t>(speed * deltaTime);
        break;
    default:
        break;
    }

    // Check for collisions or out-of-bounds and handle accordingly
    // If the bullet hits an obstacle or goes out of bounds, set isAlive to false
}

BulletDTO Bullet::getDTO() const {
    return BulletDTO(pos.x, pos.y, id, damage, speed, shooterId);
}


bool Bullet::isBulletAlive() const {
    return alive;
}

void Bullet::setAlive(bool alive) {
    this->alive = alive;
}