#include "enemy.h"

EnemyDTO::EnemyDTO(const uint32_t& x, const uint32_t& y, const uint8_t& enemy_id, uint8_t health, uint8_t damage, uint8_t speed,
                   const EnemyType& type, const EnemyStateEntity& state):
        GameElementDTO(ElementType::ENEMY),
        x(x),
        y(y),
        enemy_id(enemy_id),
        health(health),
        damage(damage),
        speed(speed),
        type(type),
        state(state) {}


uint8_t EnemyDTO::getEnemyId() const { return enemy_id; }
uint32_t EnemyDTO::getX() const { return x; }
uint32_t EnemyDTO::getY() const { return y; }

uint8_t EnemyDTO::getHealth() const { return health; }
uint8_t EnemyDTO::getDamage() const { return damage; }
uint8_t EnemyDTO::getSpeed() const { return speed; }
bool EnemyDTO::isAlive() const { return enemyIsAlive; }
EnemyType EnemyDTO::getEnemyType() const { return type; }
EnemyStateEntity EnemyDTO::getState() const { return state; }

std::unique_ptr<DTO> EnemyDTO::clone() const {
    return std::make_unique<EnemyDTO>(*this);
}