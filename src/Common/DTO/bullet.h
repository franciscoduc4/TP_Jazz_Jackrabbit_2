#ifndef BULLET_DTO_H_
#define BULLET_DTO_H_

#include "../sprite.h"

#include "gameElement.h"

class BulletDTO: public GameElementDTO {
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
    uint16_t getX() const;
    uint16_t getY() const;
    int getDamage() const;
    int getSpeed() const;
    bool isAlive() const;
    int getShooterId() const;
};

#endif  // BULLET_DTO_H_
