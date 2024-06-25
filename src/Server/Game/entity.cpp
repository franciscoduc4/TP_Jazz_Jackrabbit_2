#include "entity.h"

Entity::Entity(Vector<uint32_t> pos, uint8_t id, uint8_t health, Direction dir, EntityType type):
        initialPos(pos),
        pos(pos),
        id(id),
        health(health),
        initialHealth(health),
        dir(dir),
        type(type),
        isDead(false) {}


Vector<uint32_t> Entity::getPosition() const { return pos; }

uint8_t Entity::getId() const { return id; }

Direction Entity::getDirection() const { return dir; }

uint8_t Entity::getHealth() const { return health; }

Vector<uint32_t> Entity::getMapPosition(uint8_t movesPerCell) const {
    std::cout << "[ENTITY] Position: " << pos << " movesPerCell: " << (int)movesPerCell
              << std::endl;
    if (movesPerCell == 0) {
        return pos;
    }
    return {static_cast<uint8_t>(pos.x / movesPerCell), static_cast<uint8_t>(pos.y / movesPerCell)};
}

void Entity::recvDamage(uint8_t damage) {
    if (health - damage <= 0) {
        health = 0;
        die();
        std::cout << "[ENTITY] Died" << std::endl;
        return;
    }
    health -= damage;
    std::cout << "[ENTITY] Received damage: " << (int)damage << std::endl;
    std::cout << "[ENTITY] Health post damage: " << (int)health << std::endl;
}

bool Entity::getIsDead() const { return isDead; }

void Entity::die() { isDead = true; }

void Entity::setPosition(Vector<uint32_t> newPosition) { pos = newPosition; }

void Entity::setDirection(Direction newDir) { dir = newDir; }

bool Entity::isAlive() const { return !isDead; }

uint8_t Entity::getDistanceTo(std::shared_ptr<Entity> other) const {
    return static_cast<uint8_t>(pos.distance(other->getPosition()));
}

void Entity::heal(uint8_t healQnt) {
    health += healQnt;
    if (health > initialHealth) {
        health = initialHealth;
    }
}

EntityType Entity::getType() const { return type; }