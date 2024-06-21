#ifndef FULLFLOOR_H
#define FULLFLOOR_H

#include "obstacle.h"

class FullFloor : public Obstacle {
public:
    FullFloor(GameMap& gameMap, Vector<uint32_t> position);

     void update(double deltaTime) override;

    ObstacleType getObstacleType() const { return ObstacleType::FULL_FLOOR; }
};

#endif // FULLFLOOR_H
