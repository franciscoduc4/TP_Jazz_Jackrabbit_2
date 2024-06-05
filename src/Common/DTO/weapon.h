#ifndef WEAPON_DTO_H_
#define WEAPON_DTO_H_

#include <memory>

#include "bullet.h"
#include "gameElement.h"
#include "../sprite.h"

class WeaponDTO: public GameElementDTO {
private:
    uint8_t weaponId;
    uint16_t x;
    uint16_t y;
    int shootSpeed;
    BulletDTO bullet;
    int damage;
    int ammo;


    public:
        WeaponDTO(uint8_t weaponId, uint16_t x, uint16_t y, int damage, 
        int ammo);
        uint16_t getX() const;
        uint16_t getY() const;
        uint8_t getWeaponId() const;
        Sprite getSprite() const;
        int getShootSpeed() const;
        std::unique_ptr<BulletDTO> getBullet() const;
        int getDamage() const;
        int getAmmo() const;
        void setAmmo(int ammo);

};

#endif  // WEAPON_H_
