#ifndef Column_H
#define Column_H

#include "obstacle.h"

class Column : public Obstacle {
public:
    Column(GameMap& gameMap, Vector<uint32_t> position);

    void update(double deltaTime) override;

    ObstacleType getObstacleType() const { return ObstacleType::COLUMN; }
};

#endif // Column_H
