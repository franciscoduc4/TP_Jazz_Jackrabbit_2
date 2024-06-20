#include "bouncer.h"

#include "../../../Common/Config/ServerConfig.h"
// #define CONFIG ServerConfig::getInstance()

Bouncer::Bouncer():
        bullets(ServerConfig::getWeaponBouncerBullets()),
        maxBullets(ServerConfig::getWeaponBouncerBullets()),
        damage(ServerConfig::getWeaponBouncerDamage()),
        fireRate(ServerConfig::getWeaponBouncerFireRate()),
        lastTimeShot(-1) {}

void Bouncer::update(float time) {
    if (lastTimeShot != -1 && time - lastTimeShot >= fireRate) {
        bullets = maxBullets;
        lastTimeShot = -1;
    }
}
void Bouncer::shoot(std::vector<std::shared_ptr<Entity>>& shootingEntities, uint32_t xPos,
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

void Bouncer::reload() { bullets = maxBullets; }

bool Bouncer::isEmpty() { return bullets == 0; }

bool Bouncer::isLoaded() { return bullets == maxBullets; }

uint8_t Bouncer::getBullets() { return bullets; }

uint8_t Bouncer::getBulletsShot() { return bulletsShot; }

bool Bouncer::shootTime(float time) {
    return lastTimeShot != -1 && time - lastTimeShot >= fireRate;
}

WeaponType Bouncer::getWeaponType() { return WeaponType::BOUNCER; }

float Bouncer::getFireRate() { return fireRate; }
