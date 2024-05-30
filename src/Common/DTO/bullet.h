#ifndef BULLET_H_
#define BULLET_H_

#include "gameElement.h"
#include "../sprite.h"

class BulletDTO : public GameElementDTO {
    private:
        uint16_t x;
        uint16_t y;
        uint32_t bullet_id;
        int damage;
        int speed;
        bool bulletIsAlive;
        int shooterId;
        Sprite currentSprite;
    public:
        BulletDTO(uint16_t x, uint16_t y, uint32_t bullet_id, int damage, int speed,
                 const Sprite& currentSprite, int shooterId);
        uint32_t getBulletId() const;
        int getDamage() const;
        int getSpeed() const;
        bool isAlive() const;
        int getShooterId() const;
};

#endif // BULLET_H_

