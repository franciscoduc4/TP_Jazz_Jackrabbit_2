#include "weapon.h"

WeaponDTO::WeaponDTO(uint8_t weaponId, uint32_t x, uint32_t y, int damage, int ammo):
        weaponId(weaponId),
        x(x),
        y(y),
        shootSpeed(0),
        bullet(x, y, 0, damage, 0, 0),  // bullet is not used
        damage(damage),
        ammo(ammo) {}

uint32_t WeaponDTO::getX() const { return x; }

uint32_t WeaponDTO::getY() const { return y; }


int WeaponDTO::getDamage() const { return damage; }

int WeaponDTO::getAmmo() const { return ammo; }

void WeaponDTO::setAmmo(int ammo) { this->ammo = ammo; }

uint8_t WeaponDTO::getWeaponId() const { return weaponId; }

int WeaponDTO::getShootSpeed() const { return shootSpeed; }

std::unique_ptr<BulletDTO> WeaponDTO::getBullet() const {
    return std::make_unique<BulletDTO>(0, 0, 0, 0, 0, 0);
}
