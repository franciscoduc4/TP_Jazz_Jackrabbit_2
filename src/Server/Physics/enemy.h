#ifndef ENEMY_H_H
#define ENEMY_H_H

#include <iostream>
#include <string>
#include "../../Common/Models/vector.h"
#include "character.h"

class Enemy {
protected:
    Vector position;
    Vector velocity;
    Vector size;  // ancho x alto
    int health;
    int damage;
    bool isAlive;

public:
    explicit Enemy(Vector startPosition):
            position(startPosition), velocity({0, 0}), health(100), isAlive(true) {}

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

    std::string serialize() const {
        return std::to_string(position.x) + " " + std::to_string(position.y) + " " +
               std::to_string(health) + " " + std::to_string(isAlive);
    }

    void onCollision(Character& target) { target.takeDamage(damage); }

    Vector getSize() const { return size; }

    Vector getPosition() const { return position; }

    bool getIsAlive() const { return isAlive; }

    virtual void attack(Character& target) = 0;
};

class WalkingEnemy: public Enemy {};

class FlyingEnemy: public Enemy {};

class JumpingEnemy: public Enemy {};

#endif  // ENEMY_H_H
