#include "bullet.h"

BulletDTO::BulletDTO(const uint32_t& x, const uint32_t& y, const uint8_t& bullet_id, int damage, int speed,
                     int shooterId):
        GameElementDTO(ElementType::BULLET),
        x(x),
        y(y),
        bullet_id(bullet_id),
        damage(damage),
        speed(speed),
        bulletIsAlive(true),
        shooterId(shooterId) {}

uint8_t BulletDTO::getBulletId() const { return bullet_id; }

uint32_t BulletDTO::getX() const { return x; }

uint32_t BulletDTO::getY() const { return y; }

int BulletDTO::getDamage() const { return damage; }

int BulletDTO::getSpeed() const { return speed; }

bool BulletDTO::isAlive() const { return bulletIsAlive; }

int BulletDTO::getShooterId() const { return shooterId; }

std::unique_ptr<DTO> BulletDTO::clone() const {
    return std::make_unique<BulletDTO>(*this);
}
