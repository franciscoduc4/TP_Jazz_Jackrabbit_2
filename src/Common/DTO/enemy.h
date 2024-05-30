#ifndef ENEMY_H
#define ENEMY_H

#include <cstdint>

#include "gameElement.h"
#include "../sprite.h"

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
    Sprite currentSprite;

public:
    EnemyDTO(uint16_t x, uint16_t y, uint32_t enemy_id, int health, int damage, int speed,
             const Sprite& currentSprite);
    uint32_t getEnemyId() const;
    int getDamage() const;
    int getHealth() const;
    int getSpeed() const;
    bool isAlive() const;
};

#endif  // ENEMY_H
