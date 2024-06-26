#ifndef Column_H
#define Column_H

#include "obstacle.h"

class Column : public Obstacle {
public:
    Column(GameMap& gameMap, Vector<uint32_t> position, uint32_t width, uint32_t height);

    void update(double deltaTime) override;

    ObstacleType getObstacleType() const override { return ObstacleType::COLUMN; }

    uint32_t getWidth() const override { return ServerConfig::getColumnWidth(); }
    uint32_t getHeight() const override { return ServerConfig::getColumnHeight(); }
};

#endif // Column_H
