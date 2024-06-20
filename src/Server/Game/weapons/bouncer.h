#ifndef BOUNCER_H
#define BOUNCER_H

#include <iostream>
#include <memory>
#include <vector>

#include "../../../Common/Types/weapon.h"

#include "weapon.h"

class Bouncer: public Weapon {
private:
    uint8_t bullets;
    const uint8_t maxBullets;
    const uint8_t damage;
    const float fireRate;
    uint8_t bulletsShot = 0;
    uint8_t lastTimeShot;

public:
    Bouncer();

    void update(float time) override;

    void shoot(std::vector<std::shared_ptr<Entity>>& shootingEntities, uint32_t xPos,
               float time) override;

    void reload() override;

    bool isEmpty() override;

    bool isLoaded() override;

    uint8_t getBullets() override;

    uint8_t getBulletsShot() override;

    bool shootTime(float time) override;

    WeaponType getWeaponType() override;

    float getFireRate() override;
};

#endif  // BOUNCER_H
