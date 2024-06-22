#ifndef RIGHTLADDER_H
#define RIGHTLADDER_H

#include "obstacle.h"

class RightLadder : public Obstacle {
public:
    RightLadder(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

     void update(double deltaTime) override;

    ObstacleType getObstacleType() const { return ObstacleType::RIGHT_LADDER; }
    
    uint32_t getWidth() const { return 120; }
    uint32_t getHeight() const { return 120; }

};

#endif // RIGHTLADDER_H
