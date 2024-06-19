#ifndef ENEMY_DTO_H
#define ENEMY_DTO_H

#include <cstdint>
#include <memory>

#include "../Types/enemy.h"
#include "../Types/entity.h"
#include "dto.h"

#include "gameElement.h"

class EnemyDTO: public GameElementDTO {
private:
    uint32_t x;
    uint32_t y;
    uint8_t enemy_id;
    int health;
    int damage;
    int speed;
    bool enemyIsAlive;
    int respawnTime;
    EnemyType type;
    EnemyStateEntity state;


public:
    EnemyDTO(const uint32_t& x, const uint32_t& y, const uint8_t& enemy_id, int health, int damage, int speed,
             const EnemyType& type, const EnemyStateEntity& state);
    uint8_t getEnemyId() const;
    uint32_t getX() const;
    uint32_t getY() const;
    int getDamage() const;
    int getHealth() const;
    int getSpeed() const;
    bool isAlive() const;
    EnemyType getEnemyType() const;
    EnemyStateEntity getState() const;

    virtual std::unique_ptr<DTO> clone() const override;
};

#endif  // ENEMY_DTO_H
