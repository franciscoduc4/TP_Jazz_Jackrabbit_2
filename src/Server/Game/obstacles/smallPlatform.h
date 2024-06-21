#ifndef SMALLPLATFORM_H
#define SMALLPLATFORM_H

#include "obstacle.h"

class SmallPlatform : public Obstacle {
public:
    SmallPlatform(GameMap& gameMap, Vector<uint32_t> position);

     void update(double deltaTime) override;

    ObstacleType getObstacleType() const { return ObstacleType::SMALL_PLATFORM; }
};

#endif // SMALLPLATFORM_H
