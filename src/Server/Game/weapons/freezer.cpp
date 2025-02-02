#include "freezer.h"

#include "../../../Common/Config/ServerConfig.h"
// #define CONFIG ServerConfig::getInstance()

Freezer::Freezer():
        bullets(ServerConfig::getWeaponFreezerBullets()),
        maxBullets(ServerConfig::getWeaponFreezerBullets()),
        damage(ServerConfig::getWeaponFreezerDamage()),
        fireRate(ServerConfig::getWeaponFreezerFireRate()),
        lastTimeShot(-1) {}

void Freezer::update(float time) {
    if (lastTimeShot != -1 && time - lastTimeShot >= fireRate) {
        bullets = maxBullets;
        lastTimeShot = -1;
    }
}

void Freezer::shoot(const std::vector<std::shared_ptr<Entity>>& shootingEntities, uint32_t xPos,
                    float time) {
    lastTimeShot = time;
    bullets--;
    bulletsShot++;

    if (shootingEntities.empty())
        return;

    for (auto& entity: shootingEntities) {
        entity->recvDamage(damage, time);
    }
}

void Freezer::reload() { bullets = maxBullets; }

bool Freezer::isEmpty() { return bullets == 0; }

bool Freezer::isLoaded() { return bullets == maxBullets; }

uint8_t Freezer::getBullets() { return bullets; }

uint8_t Freezer::getBulletsShot() { return bulletsShot; }

bool Freezer::shootTime(float time) {
    return lastTimeShot != -1 && time - lastTimeShot >= fireRate;
}

WeaponType Freezer::getWeaponType() { return WeaponType::FREEZER; }

float Freezer::getFireRate() { return fireRate; }

bool Freezer::cooldown(float time) {
    return (time - lastTimeShot) > fireRate;
}

uint8_t Freezer::getDamage() { return damage; }