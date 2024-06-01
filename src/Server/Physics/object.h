#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <cstdint>
#include <utility>

class Object {

public:
    virtual int16_t getX() = 0;
    virtual int16_t getY() = 0;
    virtual int16_t getId() = 0;
    virtual int16_t getDir() = 0;
    virtual int16_t getHealth() = 0;
    virtual int16_t getMatrixX() = 0;
    virtual int16_t getMatrixY() = 0;
    virtual bool getIsDead() = 0;


    virtual void recvDmg(uint16_t dmg, float time) = 0;

    virtual void die() = 0;

    virtual void move(int16_t deltaX, int16_t deltaY)= 0;

    virtual void setPosition(int16_t newX, int16_t newY)= 0;

    virtual std::pair<int16_t, int16_t> getPosition() = 0;

    virtual bool isAlive() = 0;

    virtual void update(float time) = 0;
    virtual void interact(Object& other) = 0;
};

#endif // OBJECT_H
