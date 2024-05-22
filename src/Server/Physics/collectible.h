#ifndef COLLECTIBLE_H_H
#define COLLECTIBLE_H_H

#include "vector.h"

class Collectible {
    private:
        Vector position;
        bool isCollected;
        int valuePoints;

    public:
        Collectible(Vector startPosition, int valuePoints): position(startPosition), 
        isCollected(false), valuePoints(valuePoints) {}

        Vector getPosition() const {
            return position;
        }

        int getValuePoints() const {
            return valuePoints;
        }

        bool getIsCollected() const {
            return isCollected;
        }

        void collect() {
            isCollected = true;
        }

        void update(float deltaTime) {
            
        }

};

class Coin : public Collectible {
    public:
        explicit Coin(Vector startPosition): Collectible(startPosition, 10) {}
};

class Gem : public Collectible {
    public:
        explicit Gem(Vector startPosition): Collectible(startPosition, 50) {}
};

#endif // COLLECTIBLE_H_H

