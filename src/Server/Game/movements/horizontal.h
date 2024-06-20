#ifndef HORIZONTAL_MOVEMENT_H_
#define HORIZONTAL_MOVEMENT_H_

#include <memory>

#include "../../../Common/vector.h"
#include "../positions/position.h"
#include "../terrains/terrain.h"

class HorizontalMovement {
private:
    float speed;
    float maxSpeed;
    float acceleration;

public:
    HorizontalMovement(float maxSpeed, float acceleration);
    void accelerateRight(std::shared_ptr<Terrain> terrain);
    void accelerateLeft(std::shared_ptr<Terrain> terrain);
    void move(std::shared_ptr<Position> position, std::shared_ptr<Terrain> terrain);

    float getSpeed();
    void setSpeed(float speed);
};

#endif  // HORIZONTAL_MOVEMENT_H_