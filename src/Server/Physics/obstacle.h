#ifndef OBSTACLE_H
#define OBSTACLE_H

<<<<<<< Updated upstream
#include <iostream>

#include "entity.h"

class Obstacle: public Entity {
private:
    int16_t moves;
    int16_t x;
    int16_t y;
    int16_t id;

public:
    Obstacle(int16_t x, int16_t y, int16_t id);

    int16_t getX() override;
    int16_t getY() override;
    int16_t getMatrixX() override;
    int16_t getMatrixY() override;

    int16_t getId() override;
    void recvDmg(uint16_t dmg, float time) override;
=======
#include "entity.h"
#include <iostream>

class Obstacle : public Entity {
    private:
        int16_t moves;
        int16_t x;
        int16_t y;
        int16_t id;
    public:
        Obstacle(int16_t x, int16_t y, int16_t id);

        int16_t getX();
        int16_t getY();
        int16_t getMatrixX();
        int16_t getMatrixY();

        int16_t getId();
        void recvDamage(uint16_t dmg, float time) override;
>>>>>>> Stashed changes
}

#endif  // OBSTACLE_H
