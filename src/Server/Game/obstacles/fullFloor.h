#ifndef FULLFLOOR_H
#define FULLFLOOR_H

#include "obstacle.h"

class FullFloor : public Obstacle {
public:
    FullFloor(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

     void update(double deltaTime) override;

    ObstacleType getObstacleType() const override { return ObstacleType::FULL_FLOOR; }

    uint32_t getWidth() const override { return ServerConfig::getFullFloorWidth(); }
    uint32_t getHeight() const override { return ServerConfig::getFullFloorHeight(); }

};

#endif // FULLFLOOR_H
