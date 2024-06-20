#include "air.h"

Air::Air() { frictionCoefficient = 0.08; }

float Air::applyHorizontalFriction(float speed) {
    if (speed < 0) {
        return (speed + frictionCoefficient);
    } else {
        return (speed - frictionCoefficient);
    }
}

float Air::applyVerticalFriction(float speed) { return speed; }

float Air::getHorizontalAcceleration(float acceleration) { return (acceleration / 1.5); }

float Air::getVerticalAcceleration(float acceleration) { return 0; }