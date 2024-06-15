#ifndef ENEMY_DTO_H
#define ENEMY_DTO_H

#include <cstdint>

#include "../Types/enemy.h"
#include "../Types/entity.h"

#include "gameElement.h"

class EnemyDTO: public GameElementDTO {
private:
    uint16_t x;
    uint16_t y;
    uint8_t enemy_id;
    int health;
    int damage;
    int speed;
    bool enemyIsAlive;
    int respawnTime;
    EnemyType type;
    EnemyStateEntity state;


public:
    EnemyDTO(uint16_t x, uint16_t y, uint8_t enemy_id, int health, int damage, int speed,
             EnemyType type, EnemyStateEntity state);
    uint8_t getEnemyId() const;
    uint16_t getX() const;
    uint16_t getY() const;
    int getDamage() const;
    int getHealth() const;
    int getSpeed() const;
    bool isAlive() const;
    EnemyType getType() const;
    EnemyStateEntity getState() const;
};

#endif  // ENEMY_DTO_H
