#ifndef RIGHTLADDER_H
#define RIGHTLADDER_H

#include "obstacle.h"

class RightLadder : public Obstacle {
public:
    RightLadder(GameMap& gameMap, Vector<uint32_t> position);

     void update(double deltaTime) override;
};

#endif // RIGHTLADDER_H
