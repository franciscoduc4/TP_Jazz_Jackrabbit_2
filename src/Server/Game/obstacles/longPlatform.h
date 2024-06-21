#ifndef LONGPLATFORM_H
#define LONGPLATFORM_H

#include "obstacle.h"

class LongPlatform : public Obstacle {
public:
    LongPlatform(GameMap& gameMap, Vector<uint32_t> position);

     void update(double deltaTime) override;

    ObstacleType getObstacleType() const { return ObstacleType::LONG_PLATFORM; }
};

#endif // LONGPLATFORM_H
