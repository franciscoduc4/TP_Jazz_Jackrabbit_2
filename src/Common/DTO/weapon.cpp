#include "weapon.h"

WeaponDTO::WeaponDTO(const uint8_t& weaponId, const uint32_t& x, const uint32_t& y, int damage, int ammo):
        GameElementDTO(ElementType::WEAPON),
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
