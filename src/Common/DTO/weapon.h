#ifndef WEAPON_DTO_H_
#define WEAPON_DTO_H_

#include "gameElement.h"
#include "bullet.h"
#include "../sprite.h"
#include <memory>

class WeaponDTO: public GameElementDTO {
    private:
        uint8_t weaponId;
        uint16_t x;
        uint16_t y;
        int shootSpeed;
        BulletDTO bullet;
        int damage;
        int ammo;
        Sprite currentSprite;

    public:
        WeaponDTO(uint8_t weaponId, uint16_t x, uint16_t y, int damage, 
        int ammo, const Sprite& currentSprite);
        uint16_t getX() const;
        uint16_t getY() const;
        uint8_t getWeaponId() const;
        Sprite getSprite() const;
        int getShootSpeed() const;
        std::unique_ptr<BulletDTO> getBullet() const;
        int getDamage() const;
        int getAmmo() const;
        void setAmmo(int ammo);
        //~WeaponDTO();
};

#endif // WEAPON_H_
