#ifndef WOODLARGECOLUMN_H
#define WOODLARGECOLUMN_H

#include "obstacle.h"

class WoodLargeColumn : public Obstacle {
public:
    WoodLargeColumn(GameMap& gameMap, Vector<uint32_t> position);

    void update(double deltaTime) override;
};

#endif // WOODLARGECOLUMN_H
