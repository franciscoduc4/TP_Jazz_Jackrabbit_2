#include "position.h"

Position::Position(Vector<uint32_t> initPosition): position(initPosition) {
    maxY = 1000;
    minY = 0;
    maxX = 1000;
    minX = 0;

    std::cout << "[POSITION] Init position: " << position << " maxY: " << maxY << " minY: " << minY
              << " maxX: " << maxX << " minX: " << minX << std::endl;
}

uint32_t Position::getX() const {
    std::cout << "[POSITION] Getting X: " << position.x << std::endl;
    return position.x;
}

uint32_t Position::getY() const {
    std::cout << "[POSITION] Getting Y: " << position.y << std::endl;
    return position.y;
}

void Position::moveX(uint32_t amountToMove) {
    std::cout << "[POSITION] Moving X by: " << amountToMove << std::endl;
    if (position.x < minX) {
        position.x = minX;
        std::cout << "[POSITION] X is below minX. Setting X to minX: " << minX << std::endl;
    } else if (position.x + amountToMove > maxX) {
        position.x = maxX;
        std::cout << "[POSITION] X is above maxX after move. Setting X to maxX: " << maxX
                  << std::endl;
    } else {
        position.x += amountToMove;
        std::cout << "[POSITION] X after move: " << position.x << std::endl;
    }
}

void Position::moveY(uint32_t amountToMove) {
    std::cout << "[POSITION] Moving Y by: " << amountToMove << std::endl;
    if (position.y < minY) {
        position.y = minY;
        std::cout << "[POSITION] Y is below minY. Setting Y to minY: " << minY << std::endl;
    } else if (position.y + amountToMove > maxY) {
        position.y = maxY;
        std::cout << "[POSITION] Y is above maxY after move. Setting Y to maxY: " << maxY
                  << std::endl;
    } else {
        position.y += amountToMove;
        std::cout << "[POSITION] Y after move: " << position.y << std::endl;
    }
}
