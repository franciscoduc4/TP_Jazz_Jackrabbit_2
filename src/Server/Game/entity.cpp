#include "entity.h"

/*
 * Constructor de Entity que inicializa sus atributos.
 */
Entity::Entity(Vector<uint32_t> pos, uint8_t id, uint8_t health, Direction dir, EntityType type):
        initialPos(pos),
        pos(pos),
        id(id),
        health(health),
        initialHealth(health),
        dir(dir),
        type(type),
        isDead(false) {}

/*
 * Devuelve la posición actual de la entidad.
 */
Vector<uint32_t> Entity::getPosition() const { return pos; }

/*
 * Devuelve el ID de la entidad.
 */
uint8_t Entity::getId() const { return id; }

/*
 * Devuelve la dirección en la que se mueve la entidad.
 */
Direction Entity::getDirection() const { return dir; }

/*
 * Devuelve la salud actual de la entidad.
 */
uint8_t Entity::getHealth() const { return health; }

/*
 * Devuelve la posición en el mapa de la entidad, ajustada por el tamaño de las celdas.
 */
Vector<uint32_t> Entity::getMapPosition(uint8_t movesPerCell) const {
    std::cout << "[ENTITY] Position: " << pos << " movesPerCell: " << (int)movesPerCell << std::endl;
    if (movesPerCell == 0) {
        return pos;
    }
    return {static_cast<uint8_t>(pos.x / movesPerCell), static_cast<uint8_t>(pos.y / movesPerCell)};
}

/*
 * Recibe daño y ajusta la salud de la entidad en consecuencia.
 */
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

/*
 * Devuelve el estado de muerte de la entidad.
 */
bool Entity::getIsDead() const { return isDead; }

/*
 * Marca la entidad como muerta.
 */
void Entity::die() { isDead = true; }

/*
 * Ajusta la posición de la entidad.
 */
void Entity::setPosition(Vector<uint32_t> newPosition) { pos = newPosition; }

/*
 * Ajusta la dirección en la que se mueve la entidad.
 */
void Entity::setDirection(Direction newDir) { dir = newDir; }

/*
 * Verifica si la entidad está viva.
 */
bool Entity::isAlive() const { return !isDead; }

/*
 * Devuelve la distancia a otra entidad.
 */
uint8_t Entity::getDistanceTo(std::shared_ptr<Entity> other) const {
    return static_cast<uint8_t>(pos.distance(other->getPosition()));
}

/*
 * Cura a la entidad una cantidad específica de salud.
 */
void Entity::heal(uint8_t healQnt) {
    health += healQnt;
    if (health > initialHealth) {
        health = initialHealth;
    }
}

/*
 * Devuelve el tipo de la entidad.
 */
EntityType Entity::getType() const { return type; }
