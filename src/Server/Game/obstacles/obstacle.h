#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../entity.h"
#include "../../../Common/vector.h"
#include "../../../Common/Types/obstacles.h"

class GameMap;

class Obstacle : public Entity {
public:
    Obstacle(GameMap& gameMap, Vector<uint32_t> position);

    void update(double deltaTime) override = 0;
};

#endif // OBSTACLE_H
