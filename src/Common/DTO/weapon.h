#ifndef WEAPON_DTO_H_
#define WEAPON_DTO_H_

#include <memory>

#include "../sprite.h"

#include "bullet.h"
#include "gameElement.h"

class WeaponDTO: public GameElementDTO {
private:
    uint8_t weaponId;
    uint32_t x;
    uint32_t y;
    int shootSpeed;
    BulletDTO bullet;
    int damage;
    int ammo;


public:
    WeaponDTO();
    WeaponDTO(const uint8_t weaponId, const uint32_t x, const uint32_t y, int damage, int ammo);
    uint32_t getX() const;
    uint32_t getY() const;
    uint8_t getWeaponId() const;
    Sprite getSprite() const;
    int getShootSpeed() const;
    std::unique_ptr<BulletDTO> getBullet() const;
    int getDamage() const;
    int getAmmo() const;
    void setAmmo(int ammo);
};

#endif  // WEAPON_H_
