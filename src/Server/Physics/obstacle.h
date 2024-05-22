#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "vector.h"
#include "character.h"

class Obstacle {
    private:
        Vector position;
        Vector size; //ancho x alto
        int damage;
    public:
        Obstacle(Vector startPosition, Vector obstacleSize, int damage): 
        position(startPosition), size(obstacleSize), damage(damage) {}

        Vector getPosition() const {
            return position;
        }

        Vector getSize() const {
            return size;
        }

        int getDamage() const {
            return damage;
        }

        bool isColliding(const Character& character) const {
            Vector charPos = character.getPosition();
            return (
            charPos.x < position.x + size.x && charPos.x + 
            character.getSize().x > position.x &&
            charPos.y < position.y + size.y && charPos.y + character.getSize().y > position.y);
        }
};

#endif  // OBSTACLE_H_

