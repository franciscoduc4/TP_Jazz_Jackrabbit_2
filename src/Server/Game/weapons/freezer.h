#ifndef FREEZER_H
#define FREEZER_H

#include <iostream>
#include <memory>
#include <vector>

#include "../../../Common/Types/weapon.h"

#include "weapon.h"

class Freezer: public Weapon {
private:
    uint16_t bullets;
    const uint16_t maxBullets;
    const uint16_t damage;
    const float fireRate;
    uint32_t bulletsShot = 0;
    int16_t lastTimeShot;

public:
    Freezer();

    void update(float time) override;

    void shoot(std::vector<std::shared_ptr<Entity>>& shootingEntities, int16_t xPos,
               float time) override;

    void reload() override;

    bool isEmpty() override;

    bool isLoaded() override;

    int16_t getBullets() override;

    uint32_t getBulletsShot() override;

    bool shootTime(float time) override;

    WeaponType getWeaponType() override;

    float getFireRate() override;
};

#endif  // FREEZER_H
