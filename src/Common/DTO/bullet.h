#ifndef BULLET_DTO_H_
#define BULLET_DTO_H_

#include <memory>

#include "dto.h"
#include "gameElement.h"

class BulletDTO: public GameElementDTO {
private:
    uint32_t x;
    uint32_t y;
    uint8_t bullet_id;
    int damage;
    int speed;
    bool bulletIsAlive;
    int shooterId;

public:
    BulletDTO(const uint32_t& x, const uint32_t& y, const uint8_t& bullet_id, int damage, int speed, int shooterId);
    uint8_t getBulletId() const;
    uint32_t getX() const;
    uint32_t getY() const;
    int getDamage() const;
    int getSpeed() const;
    bool isAlive() const;
    int getShooterId() const;

    virtual std::unique_ptr<DTO> clone() const override;
};

#endif  // BULLET_DTO_H_
