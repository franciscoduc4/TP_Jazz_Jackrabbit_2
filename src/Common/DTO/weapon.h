#ifndef WEAPON_H_
#define WEAPON_H_

#include "gameElement.h"
#include "../sprite.h"

class WeaponDTO: public GameElementDTO {
    private:
        uint16_t x;
        uint16_t y;
        Sprite currentSprite;
        int damage;
        int range;
        int ammo;
        public:
        WeaponDTO(uint16_t x, uint16_t y, int damage, int range, 
        int ammo, const Sprite& currentSprite);
        uint16_t getX() const;
        uint16_t getY() const;
        Sprite getSprite() const;
        int getDamage() const;
        int getRange() const;
        int getAmmo() const;
        void setAmmo(int ammo);
        ~WeaponDTO();
};

#endif // WEAPON_H_
