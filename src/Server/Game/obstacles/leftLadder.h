#ifndef LEFTLADDER_H
#define LEFTLADDER_H

#include "obstacle.h"

class LeftLadder : public Obstacle {
public:
    LeftLadder(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

     void update(double deltaTime) override;

    ObstacleType getObstacleType() const override { return ObstacleType::LEFT_LADDER; }

    uint32_t getWidth() const override { return 120; }
    uint32_t getHeight() const override { return 120; }
};

#endif // LEFTLADDER_H
