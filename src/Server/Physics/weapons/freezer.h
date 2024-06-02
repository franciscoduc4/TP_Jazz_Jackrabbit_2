#ifndef FREEZER_H
#define FREEZER_H

#include "weapon.h"
#include "../../../Common/Types/weapon.h"
#include <vector>
#include <iostream>
#include <memory>

class Freezer : public Weapon {
private:
    uint16_t bullets;
    const uint16_t maxBullets;
    const uint16_t damage;
    const float fireRate;
    int32_t bulletsShot = 0;
    int16_t lastTimeShot;

public:
    Freezer();

    void update(float time) override;

    void shoot(std::shared_ptr<Entity>& shootingEntities, int16_t xPos, float time) override;

    void reload() override;

    bool isEmpty() override;

    bool isLoaded() override;

    int16_t getBullets() override;

    int32_t getBulletsShot() override;

    bool shootTime(float time) override;

    WeaponType getWeaponType() override;

    float getFireRate() override;
};

#endif // FREEZER_H
