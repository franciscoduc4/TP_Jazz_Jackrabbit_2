#ifndef ENEMY_H_H
#define ENEMY_H_H

#include <string>
#include "vector.h"
#include <iostream>
#include "character.h"

class Enemy {
protected:
        Vector position;
        Vector velocity;
        int health;
        int damage;
        bool isAlive;

public:
    explicit Enemy(Vector startPosition) : position(startPosition), velocity({0, 0}),
     health(100), isAlive(true) {}

    virtual ~Enemy() {}

    virtual void update(float deltaTime) {
        if (!isAlive) {
            return;
        }
        position += velocity * deltaTime;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health <= 0) {
            health = 0;
            isAlive = false;
        }
    }

    void onCollision(Character& target) {
        target.takeDamage(damage);
    
    }

    Vector getPosition() const {
        return position;
    }

    bool getIsAlive() const {
        return isAlive;
    }

    virtual void attack(Character& target) = 0;
};

class WalkingEnemy: public Enemy {

};

class FlyingEnemy: public Enemy {

};

class JumpingEnemy: public Enemy {

};

#endif // ENEMY_H_H

