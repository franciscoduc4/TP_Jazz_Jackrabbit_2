#include "blaster.h"
#include "../../../Common/Config/ServerConfig.h"
#define CONFIG ServerConfig::getInstance()

Blaster::Blaster():
        bullets(CONFIG->getWeaponBlasterBullets()),
        maxBullets(CONFIG->getWeaponBlasterBullets()),
        damage(CONFIG->getWeaponBlasterDamage()),
        fireRate(CONFIG->getWeaponBlasterFireRate()),
        lastTimeShot(-1) {}  

void Blaster::update(float time) {
    if (lastTimeShot != -1 && time - lastTimeShot >= fireRate) {
        bullets = maxBullets;
        lastTimeShot = -1;
    }
}

void Blaster::shoot(std::vector<std::shared_ptr<Entity>>& shootingEntities, int16_t xPos,
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

void Blaster::reload() { bullets = maxBullets; }

bool Blaster::isEmpty() { return bullets == 0; }

bool Blaster::isLoaded() { return bullets == maxBullets; }

int16_t Blaster::getBullets() { return bullets; }

uint32_t Blaster::getBulletsShot() { return bulletsShot; }

bool Blaster::shootTime(float time) {
    return lastTimeShot != -1 && time - lastTimeShot >= fireRate;
}

WeaponType Blaster::getWeaponType() { return WeaponType::BLASTER; }

float Blaster::getFireRate() { return fireRate; }
