#ifndef VERTICAL_MOVEMENT_H_
#define VERTICAL_MOVEMENT_H_

#include "../../../Common/Config/ServerConfig.h"
#include "../../../Common/vector.h"
#include "../positions/position.h"
#include "../terrains/terrain.h"

class VerticalMovement {
private:
    float speed;
    float strength;
    float gravity;

public:
    explicit VerticalMovement(float strength);
    void jump(std::shared_ptr<Terrain> terrain);
    void move(std::shared_ptr<Position> position);

    void applyGravity();

    float getSpeed();
    void setSpeed(float speed);
};

#endif  // VERTICAL_MOVEMENT_H_