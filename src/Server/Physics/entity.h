#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "../../Common/Types/direction.h"
#include "../../Common/vector.h"

class Entity {
public:
    virtual Vector<int16_t> getPosition() = 0;
    virtual int16_t getId() = 0;
    virtual Direction getDir() = 0;
    virtual int16_t getHealth() = 0;
    virtual Vector<int16_t> getMapPosition() = 0;
    virtual bool getIsDead() = 0;
    virtual void recvDamage(uint16_t damage, float time) = 0;
    virtual void die() = 0;
    virtual void move(Vector<float> delta) = 0;
    virtual void setPosition(Vector<int16_t> newPosition) = 0;
    virtual bool isAlive() = 0;
    virtual void update(float time) = 0;
    virtual void interact(std::shared_ptr<Entity>& other) = 0;
    virtual std::vector<std::shared_ptr<Entity>> getTargets() = 0;
};

#endif  // ENTITY_H
