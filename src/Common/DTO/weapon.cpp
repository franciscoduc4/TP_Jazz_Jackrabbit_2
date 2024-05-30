#include "weapon.h"

WeaponDTO(uint16_t x, uint16_t y, int damage, int range, 
        int ammo, const Sprite& currentSprite) :
        x(x),
        y(y),
        damage(damage),
        range(range),
        ammo(ammo),
        currentSprite(currentSprite) {}

uint16_t WeaponDTO::getX() const { return x; }

uint16_t WeaponDTO::getY() const { return y; }

Sprite WeaponDTO::getSprite() const { return currentSprite; }

int WeaponDTO::getDamage() const { return damage; }

int WeaponDTO::getRange() const { return range; }

int WeaponDTO::getAmmo() const { return ammo; }

void WeaponDTO::setAmmo(int ammo) { this->ammo = ammo; }


