#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

#include "../../Common/Config/ServerConfig.h"
#include "../../Common/Types/direction.h"
#include "../../Common/vector.h"

class Entity {
protected:
    Vector<int16_t> pos;
    int16_t id;
    int16_t health;
    int16_t initialHealth;
    Direction dir;
    bool isDead = false;

public:
    Entity(Vector<int16_t> pos, int16_t id, int16_t health, Direction dir);

    Vector<int16_t> getPosition() const;

    int16_t getId() const;

    Direction getDirection() const;

    int16_t getHealth() const;

    Vector<int16_t> getMapPosition(int16_t movesPerCell) const;

    bool getIsDead() const;

    virtual void recvDamage(uint16_t damage, float time);

    virtual void die(float time);

    void setPosition(Vector<int16_t> newPosition);

    void setDirection(Direction newDir);

    bool isAlive() const;

    int16_t getDistanceTo(std::shared_ptr<Entity> other) const;
};

#endif  // ENTITY_H
