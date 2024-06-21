#ifndef LEFTLADDER_H
#define LEFTLADDER_H

#include "obstacle.h"

class LeftLadder : public Obstacle {
public:
    LeftLadder(GameMap& gameMap, Vector<uint32_t> position);

     void update(double deltaTime) override;

    ObstacleType getObstacleType() const { return ObstacleType::LEFT_LADDER; }
};

#endif // LEFTLADDER_H
