#include "weapon.h"

WeaponDTO::WeaponDTO(uint8_t weaponId, uint16_t x, uint16_t y, int damage, 
        int ammo, const Sprite& currentSprite) :
        weaponId(weaponId),
        x(x),
        y(y),
        shootSpeed(0),
        bullet(x, y, 0, damage, 0, currentSprite, 0),  // bullet is not used
        damage(damage),
        ammo(ammo),
        currentSprite(currentSprite) {}

uint16_t WeaponDTO::getX() const { return x; }

uint16_t WeaponDTO::getY() const { return y; }

Sprite WeaponDTO::getSprite() const { return currentSprite; }

int WeaponDTO::getDamage() const { return damage; }

int WeaponDTO::getAmmo() const { return ammo; }

void WeaponDTO::setAmmo(int ammo) { this->ammo = ammo; }

uint8_t WeaponDTO::getWeaponId() const { return weaponId; }

int WeaponDTO::getShootSpeed() const { return shootSpeed; }

std::unique_ptr<BulletDTO> WeaponDTO::getBullet() const 
{ return std::make_unique<BulletDTO>(0, 0, 0,0, 0, currentSprite, 0); }

