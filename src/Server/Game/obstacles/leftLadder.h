#ifndef LEFTLADDER_H
#define LEFTLADDER_H

#include "obstacle.h"

class LeftLadder : public Obstacle {
public:
    LeftLadder(GameMap& gameMap, Vector<uint32_t> position);

     void update(double deltaTime) override;
};

#endif // LEFTLADDER_H
