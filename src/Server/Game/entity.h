#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

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

    virtual Vector<int16_t> getPosition() const;

    virtual int16_t getId() const;

    virtual Direction getDirection() const;

    virtual int16_t getHealth() const;

    virtual Vector<int16_t> getMapPosition(int16_t movesPerCell) const;

    virtual bool getIsDead() const;

    virtual void recvDamage(uint16_t damage, float time) = 0;

    virtual void die(float time);

    virtual void move(Vector<int16_t> delta);

    virtual void setPosition(Vector<int16_t> newPosition);

    virtual void setDirection(Direction newDir);

    virtual bool isAlive() const;

    virtual void update(float time) = 0;

    virtual void interact(std::shared_ptr<Entity>& other) = 0;

    virtual std::vector<std::shared_ptr<Entity>> getTargets() = 0;

    virtual int16_t getDistanceTo(std::shared_ptr<Entity> other) const;
};

#endif  // ENTITY_H
