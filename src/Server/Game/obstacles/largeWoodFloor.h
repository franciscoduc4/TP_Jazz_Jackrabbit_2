#ifndef LARGEWOODFLOOR_H
#define LARGEWOODFLOOR_H

#include "obstacle.h"

class LargeWoodFloor : public Obstacle {
public:
    LargeWoodFloor(GameMap& gameMap, Vector<uint32_t> position);

     void update(double deltaTime) override;
};

#endif // LARGEWOODFLOOR_H
