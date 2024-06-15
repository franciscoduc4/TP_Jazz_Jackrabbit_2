#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

#include "../../Common/Config/ServerConfig.h"
#include "../../Common/Types/direction.h"
#include "../../Common/Types/entity.h"
#include "../../Common/vector.h"

class Entity {
protected:
    Vector<uint8_t> pos;
    uint8_t id;
    uint8_t health;
    uint8_t initialHealth;
    Direction dir;
    EntityType type;
    bool isDead = false;

public:
    Entity(Vector<uint8_t> pos, uint8_t id, uint8_t health, Direction dir, EntityType type);

    Vector<uint8_t> getPosition() const;

    uint8_t getId() const;

    Direction getDirection() const;

    uint8_t getHealth() const;

    Vector<uint8_t> getMapPosition(uint8_t movesPerCell) const;

    bool getIsDead() const;

    virtual void recvDamage(uint8_t damage, float time);

    virtual void die(float time);

    void setPosition(Vector<uint8_t> newPosition);

    void setDirection(Direction newDir);

    bool isAlive() const;

    uint8_t getDistanceTo(std::shared_ptr<Entity> other) const;

    void heal(uint8_t healQnt);

    EntityType getType() const;
};

#endif  // ENTITY_H
