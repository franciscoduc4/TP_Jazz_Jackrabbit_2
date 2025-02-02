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
    Vector<uint32_t> initialPos;
    Vector<uint32_t> pos;
    uint8_t id;
    uint8_t health;
    uint8_t initialHealth;
    Direction dir;
    EntityType type;
    bool isDead = false;

public:
    Entity(Vector<uint32_t> pos, uint8_t id, uint8_t health, Direction dir, EntityType type);


    Vector<uint32_t> getPosition() const;

    uint8_t getId() const;

    Direction getDirection() const;

    uint8_t getHealth() const;

    Vector<uint32_t> getMapPosition(uint8_t movesPerCell) const;

    bool getIsDead() const;

    virtual void recvDamage(uint8_t damage, float time) {}
    virtual void recvDamage(uint8_t damage);

    virtual void die(float time) {}
    virtual void die();

    void setPosition(Vector<uint32_t> newPosition);

    void setDirection(Direction newDir);

    bool isAlive() const;
    bool isEntityDead() { return health <= 0; }

    uint8_t getDistanceTo(std::shared_ptr<Entity> other) const;

    void heal(uint8_t healQnt);

    EntityType getType() const;

    virtual void update(double deltaTime) = 0;


    Vector<uint32_t> getInitialPos() const { return initialPos; }
};

#endif  // ENTITY_H
