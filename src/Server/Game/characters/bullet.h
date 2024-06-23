#ifndef BULLET_CHARACTER_H
#define BULLET_CHARACTER_H

#include "../entity.h"
#include <vector>
#include "../../../Common/DTO/bullet.h"


class Bullet : public Entity {
public:
    Bullet(Vector<uint32_t> pos, Direction dir, uint32_t damage, uint32_t speed, uint8_t shooterId);

    void update(double deltaTime) override;
    BulletDTO getDTO() const;

    bool isBulletAlive() const;
    void setAlive(bool alive);

private:
    Direction dir;
    uint32_t damage;
    uint32_t speed;
    uint8_t shooterId;
    bool alive;
};

#endif // BULLET_CHARACTER_H