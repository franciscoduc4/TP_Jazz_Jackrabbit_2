#ifndef ENEMY_DTO_H
#define ENEMY_DTO_H

#include <cstdint>

#include "../Types/enemy.h"
#include "../Types/entity.h"

#include "gameElement.h"

class EnemyDTO: public GameElementDTO {
private:
    uint32_t x;
    uint32_t y;
    uint8_t enemy_id;
    uint8_t health;
    uint8_t damage;
    uint8_t speed;
    bool enemyIsAlive;
    uint8_t respawnTime;
    EnemyType type;
    EnemyStateEntity state;


public:
    EnemyDTO(const uint32_t& x, const uint32_t& y, const uint8_t& enemy_id, uint8_t health, uint8_t damage, uint8_t speed,
             const EnemyType& type, const EnemyStateEntity& state);
    uint8_t getEnemyId() const;
    uint32_t getX() const;
    uint32_t getY() const;
    uint8_t getDamage() const;
    uint8_t getHealth() const;
    uint8_t getSpeed() const;
    bool isAlive() const;
    EnemyType getType() const;
    EnemyStateEntity getState() const;
};

#endif  // ENEMY_DTO_H
