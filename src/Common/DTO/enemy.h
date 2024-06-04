#ifndef ENEMY_DTO_H
#define ENEMY_DTO_H

#include <cstdint>

#include "gameElement.h"

class EnemyDTO: public GameElementDTO {
private:
    uint16_t x;
    uint16_t y;
    uint32_t enemy_id;
    int health;
    int damage;
    int speed;
    bool enemyIsAlive;
    int respawnTime;


public:
    EnemyDTO(uint16_t x, uint16_t y, uint32_t enemy_id, int health, int damage, int speed);
    uint32_t getEnemyId() const;
    uint16_t getX() const;
    uint16_t getY() const;
    int getDamage() const;
    int getHealth() const;
    int getSpeed() const;
    bool isAlive() const;
};

#endif  // ENEMY_DTO_H
