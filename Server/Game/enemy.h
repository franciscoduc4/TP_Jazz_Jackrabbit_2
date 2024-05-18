#ifndef ENEMY_H_H
#define ENEMY_H_H

#include <string>

class Enemy {
    protected:
        int x;
        int y;
        int health;
        int damage;
        int points;
        float respawnTime;
        float dropProbability;
        std::string type;

    public:
        Enemy(int x, int y, int health, int damage, int points, float respawnTime, 
        float dropProbability, const std::string& type)
        : x(x), y(y), health(health), damage(damage), points(points), 
        respawnTime(respawnTime), dropProbability(dropProbability), type(type) {}
        
        virtual void move() = 0;
        virtual void attack() = 0;
        virtual ~Enemy() = default;

        int getX() const { return x; }
        int getY() const { return y; }
        int getHealth() const { return health; }
        int getDamage() const { return damage; }
        int getPoints() const { return points; }
        float getRespawnTime() const { return respawnTime; }
        float getDropProbability() const { return dropProbability; }
        std::string getType() const { return type; }
};

class WalkingEnemy: public Enemy {
    public:
        WalkingEnemy(int x, int y, int health, int damage, 
        int points, float respawnTime, float dropProbability)
        : Enemy(x, y, health, damage, points, respawnTime, dropProbability, "WalkingEnemy") {}


    void move() override {}
    void attack() override {}
};

class FlyingEnemy: public Enemy {
    public:
        FlyingEnemy(int x, int y, int health, int damage, int points, 
        float respawnTime, float dropProbability)
        : Enemy(x, y, health, damage, points, respawnTime, dropProbability, "FlyingEnemy") {}

    void move() override {}
    void attack() override {}
};

#endif // ENEMY_H_H

