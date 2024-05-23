#ifndef WEAPON_H_
#define WEAPON_H_

#include <memory>
#include <string>

#include "../../Common/Models/vector.h"

#include "projectile.h"


class Weapon {
private:
    std::string name;
    int ammo;
    float fireRate;  // Tiempo entre disparos en segundos
    float projectileSpeed;
    int damage;
    float lastShotTime;

public:
    Weapon(std::string name, int ammo, float fireRate, float projectileSpeed, int damage):
            name(name),
            ammo(ammo),
            fireRate(fireRate),
            projectileSpeed(projectileSpeed),
            damage(damage),
            lastShotTime(0) {}


    bool canShoot(float currentTime) { return (currentTime - lastShotTime >= fireRate); }

    std::unique_ptr<Projectile> shoot(Vector position, Vector direction, float currentTime) {
        if (canShoot(currentTime)) {
            lastShotTime = currentTime;
            if (ammo > 0) {
                ammo--;
            }
            return std::make_unique<Projectile>(position, direction * projectileSpeed, damage);
        }
        return nullptr;
    }

    bool hasInfiniteAmmo() const { return ammo < 0; }

    int getAmmo() const { return ammo; }

    void addAmmo(int amount) { ammo += amount; }
};

#endif  // WEAPON_H_
