#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <map>

#include "../../../Common/Config/ServerConfig.h"
#include "../../../Common/Types/direction.h"
#include "../../../Common/Types/terrain.h"
#include "../../../Common/vector.h"
#include "../positions/position.h"
#include "../terrains/terrain.h"

#include "horizontal.h"
#include "vertical.h"

class Movement {
private:
    HorizontalMovement horizontalMovement;
    VerticalMovement verticalMovement;

    TerrainType currentTerrain;
    std::map<TerrainType, std::shared_ptr<Terrain>> terrains;

public:
    Movement();
    void accelerate(Direction direction);
    void move(std::shared_ptr<Position> position);
    float getHorizontalSpeed();
    float getVerticalSpeed();
    void setHorizontalSpeed(float speed);
    void setVerticalSpeed(float speed);
};

#endif  // MOVEMENT_H_