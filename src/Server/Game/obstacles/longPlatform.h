#ifndef LONGPLATFORM_H
#define LONGPLATFORM_H

#include "obstacle.h"

class LongPlatform : public Obstacle {
public:
    LongPlatform(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

     void update(double deltaTime) override;

    ObstacleType getObstacleType() const { return ObstacleType::LONG_PLATFORM; }

    uint32_t getWidth() const { return 150; }
    uint32_t getHeight() const { return 30; }
};

#endif // LONGPLATFORM_H
