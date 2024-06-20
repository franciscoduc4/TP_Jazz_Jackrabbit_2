#include "entity.h"


Entity::Entity(Vector<uint32_t> position, uint8_t id, uint8_t health, Direction dir,
               EntityType type):
        position(position),
        id(id),
        health(health),
        initialHealth(health),
        dir(dir),
        type(type),
        isDead(false) {}

Vector<uint32_t> Entity::getPosition() const { return position; }

uint8_t Entity::getId() const { return id; }

Direction Entity::getDirection() const { return dir; }

uint8_t Entity::getHealth() const { return health; }

Vector<uint32_t> Entity::getMapPosition(uint8_t movesPerCell) const {
    std::cout << "[ENTITY] Position: " << position << " movesPerCell: " << (int)movesPerCell
              << std::endl;
    return {static_cast<uint8_t>(position.x / movesPerCell),
            static_cast<uint8_t>(position.y / movesPerCell)};
}

void Entity::recvDamage(uint8_t damage, float time) {
    health -= damage;
    if (health <= 0) {
        die(time);
    }
}

bool Entity::getIsDead() const { return isDead; }

void Entity::die(float time) { isDead = true; }

void Entity::setPosition(Vector<uint32_t> newPosition) { position = newPosition; }

void Entity::setDirection(Direction newDir) { dir = newDir; }

bool Entity::isAlive() const { return !isDead; }

uint8_t Entity::getDistanceTo(std::shared_ptr<Entity> other) const {
    return static_cast<uint8_t>(position.distance(other->getPosition()));
}

void Entity::heal(uint8_t healQnt) {
    health += healQnt;
    if (health > initialHealth) {
        health = initialHealth;
    }
}

EntityType Entity::getType() const { return type; }