#ifndef SMALLPLATFORM_H
#define SMALLPLATFORM_H

#include "obstacle.h"

class SmallPlatform : public Obstacle {
public:
    SmallPlatform(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

     void update(double deltaTime) override;

    ObstacleType getObstacleType() const override { return ObstacleType::SMALL_PLATFORM; }

    uint32_t getWidth() const override { return ServerConfig::getSmallPlatformWidth(); }
    uint32_t getHeight() const override { return ServerConfig::getSmallPlatformHeight(); }
};

#endif // SMALLPLATFORM_H
