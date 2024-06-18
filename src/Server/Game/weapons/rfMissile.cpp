#include "rfMissile.h"

#include "../../../Common/Config/ServerConfig.h"
// #define CONFIG ServerConfig::getInstance()

RFMissile::RFMissile():
        bullets(ServerConfig::getWeaponRFMissileBullets()),
        maxBullets(ServerConfig::getWeaponRFMissileBullets()),
        damage(ServerConfig::getWeaponRFMissileDamage()),
        fireRate(ServerConfig::getWeaponRFMissileFireRate()),
        lastTimeShot(-1) {}

void RFMissile::update(float time) {
    if (lastTimeShot != -1 && time - lastTimeShot >= fireRate) {
        bullets = maxBullets;
        lastTimeShot = -1;
    }
}

void RFMissile::shoot(std::vector<std::shared_ptr<Entity>>& shootingEntities, uint8_t xPos,
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

void RFMissile::reload() { bullets = maxBullets; }

bool RFMissile::isEmpty() { return bullets == 0; }

bool RFMissile::isLoaded() { return bullets == maxBullets; }

uint8_t RFMissile::getBullets() { return bullets; }

uint8_t RFMissile::getBulletsShot() { return bulletsShot; }

bool RFMissile::shootTime(float time) {
    return lastTimeShot != -1 && time - lastTimeShot >= fireRate;
}

WeaponType RFMissile::getWeaponType() { return WeaponType::RFMISSILE; }

float RFMissile::getFireRate() { return fireRate; }
