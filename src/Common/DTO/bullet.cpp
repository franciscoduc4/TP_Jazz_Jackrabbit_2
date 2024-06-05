#include "bullet.h"

BulletDTO::BulletDTO(uint16_t x, uint16_t y, uint32_t bullet_id, int damage, int speed,
                     const Sprite& currentSprite, int shooterId):
        x(x),
        y(y),
        bullet_id(bullet_id),
        damage(damage),
        speed(speed),
        bulletIsAlive(true),
        shooterId(shooterId),
        currentSprite(currentSprite){}

uint32_t BulletDTO::getBulletId() const { return bullet_id; }

uint16_t BulletDTO::getX() const { return x; };

uint16_t BulletDTO::getY() const { return y; };

int BulletDTO::getDamage() const { return damage; }

int BulletDTO::getSpeed() const { return speed; }

bool BulletDTO::isAlive() const { return bulletIsAlive; }

int BulletDTO::getShooterId() const { return shooterId; }
