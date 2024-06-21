#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../entity.h"
#include "../../../Common/vector.h"
#include "../../../Common/Types/obstacles.h"
#include "../../../Common/DTO/tile.h"

class GameMap;

class Obstacle : public Entity {
private:
    Vector<uint32_t> position;
public:
    Obstacle(GameMap& gameMap, Vector<uint32_t> position);

    void update(double deltaTime) override;

    virtual ObstacleType getObstacleType() const = 0;

    TileDTO getDTO();
};

#endif // OBSTACLE_H
