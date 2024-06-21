#ifndef WOODFLOOR_H
#define WOODFLOOR_H

#include "obstacle.h"

class WoodFloor : public Obstacle {
public:
    WoodFloor(GameMap& gameMap, Vector<uint32_t> position);

     void update(double deltaTime) override;

    ObstacleType getObstacleType() const { return ObstacleType::WOOD_FLOOR; }
};

#endif // WOODFLOOR_H
