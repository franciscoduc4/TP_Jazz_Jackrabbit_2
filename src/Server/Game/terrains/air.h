#ifndef AIR_TERRAIN_H_
#define AIR_TERRAIN_H_

#include "terrain.h"

class Air: public Terrain {

public:
    Air();
    float applyHorizontalFriction(float speed) override;
    float applyVerticalFriction(float speed) override;

    float getHorizontalAcceleration(float acceleration) override;
    float getVerticalAcceleration(float acceleration) override;
};


#endif /* AIR_TERRAIN_H_ */
