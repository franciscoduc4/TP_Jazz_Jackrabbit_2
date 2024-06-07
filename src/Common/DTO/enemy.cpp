#include "enemy.h"

EnemyDTO::EnemyDTO(uint16_t x, uint16_t y, uint32_t enemy_id, int health, int damage, int speed,
                   EnemyType type, EnemyStateEntity state):
        x(x),
        y(y),
        enemy_id(enemy_id),
        health(health),
        damage(damage),
        speed(speed),
        type(type),
        state(state) {}


uint32_t EnemyDTO::getEnemyId() const { return enemy_id; }
uint16_t EnemyDTO::getX() const { return x; }
uint16_t EnemyDTO::getY() const { return y; }

int EnemyDTO::getHealth() const { return health; }
int EnemyDTO::getDamage() const { return damage; }
int EnemyDTO::getSpeed() const { return speed; }
bool EnemyDTO::isAlive() const { return enemyIsAlive; }
EnemyType EnemyDTO::getType() const { return type; }
EnemyStateEntity EnemyDTO::getState() const { return state; }
