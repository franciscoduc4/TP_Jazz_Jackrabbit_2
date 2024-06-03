#include "enemy.h"

EnemyDTO::EnemyDTO(uint16_t x, uint16_t y, uint32_t enemy_id, int health, int damage, int speed,
                   const Sprite& currentSprite):
        x(x),
        y(y),
        enemy_id(enemy_id),
        health(health),
        damage(damage),
        speed(speed),
        currentSprite(currentSprite){}


uint32_t EnemyDTO::getEnemyId() const { return enemy_id; }
int EnemyDTO::getHealth() const { return health; }
int EnemyDTO::getDamage() const { return damage; }
int EnemyDTO::getSpeed() const { return speed; }
bool EnemyDTO::isAlive() const { return enemyIsAlive; }
