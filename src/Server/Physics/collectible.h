#ifndef COLLECTIBLE_H_H
#define COLLECTIBLE_H_H

#include "../../Common/Models/vector.h"
#include <string>

class Collectible {
private:
    Vector position;
    bool isCollected;
    int valuePoints;

public:
    Collectible(Vector startPosition, int valuePoints):
            position(startPosition), isCollected(false), valuePoints(valuePoints) {}

    Vector getPosition() const { return position; }

    int getValuePoints() const { return valuePoints; }

    bool getIsCollected() const { return isCollected; }

    void collect() { isCollected = true; }

    void update(float deltaTime) {}

    std::string serialize() const {
        return std::to_string(position.x) + " " + std::to_string(position.y) + " " +
               std::to_string(valuePoints);
    }
};

class Coin: public Collectible {
public:
    explicit Coin(Vector startPosition): Collectible(startPosition, 10) {}
};

class Gem: public Collectible {
public:
    explicit Gem(Vector startPosition): Collectible(startPosition, 50) {}
};

#endif  // COLLECTIBLE_H_H
