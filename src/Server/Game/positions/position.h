#ifndef POSITION_H_
#define POSITION_H_

#include <cstdint>

#include "../../../Common/vector.h"

class Position {
private:
    Vector<uint32_t> position;
    uint32_t minY;
    uint32_t maxY;
    uint32_t minX;
    uint32_t maxX;

public:
    Position(Vector<uint32_t> initPosition);

    uint32_t getX() const;
    uint32_t getY() const;

    void moveX(uint32_t amountToMove);
    void moveY(uint32_t amountToMove);
};

#endif  // POSITION_H_