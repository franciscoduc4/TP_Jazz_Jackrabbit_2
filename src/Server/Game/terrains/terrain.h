#ifndef TERRAIN_H_
#define TERRAIN_H_


class Terrain {

public:
    virtual ~Terrain() = default;
    virtual float applyHorizontalFriction(float speed) = 0;
    virtual float applyVerticalFriction(float speed) = 0;

    virtual float getHorizontalAcceleration(float acceleration) = 0;
    virtual float getVerticalAcceleration(float strength) = 0;

protected:
    float frictionCoefficient{};
};


#endif /* TERRAIN_H_ */
