#include "entity.h"

Entity::Entity(Vector<int16_t> pos, int16_t id, int16_t health, Direction dir):
        pos(pos), id(id), health(health), initialHealth(health), dir(dir), isDead(false) {}

Vector<int16_t> Entity::getPosition() const { return pos; }

int16_t Entity::getId() const { return id; }

Direction Entity::getDirection() const { return dir; }

int16_t Entity::getHealth() const { return health; }

Vector<int16_t> Entity::getMapPosition(int16_t movesPerCell) const {
    return {static_cast<int16_t>(pos.x / movesPerCell), static_cast<int16_t>(pos.y / movesPerCell)};
}

bool Entity::getIsDead() const { return isDead; }

void Entity::die(float time) { isDead = true; }

void Entity::move(Vector<int16_t> delta) { pos += delta; }

void Entity::setPosition(Vector<int16_t> newPosition) { pos = newPosition; }

void Entity::setDirection(Direction newDir) { dir = newDir; }

bool Entity::isAlive() const { return !isDead; }

int16_t Entity::getDistanceTo(std::shared_ptr<Entity> other) const {
    return static_cast<int16_t>(pos.distance(other->getPosition()));
}
