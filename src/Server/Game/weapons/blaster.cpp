#include "blaster.h"

#include "../../../Common/Config/ServerConfig.h"
// #define CONFIG ServerConfig::getInstance()

Blaster::Blaster():
        bullets(ServerConfig::getWeaponBlasterBullets()),
        maxBullets(ServerConfig::getWeaponBlasterBullets()),
        damage(ServerConfig::getWeaponBlasterDamage()),
        fireRate(ServerConfig::getWeaponBlasterFireRate()),
        lastTimeShot(-1) {}

void Blaster::update(float time) {
    // if (lastTimeShot != -1 && time - lastTimeShot >= fireRate) {
    //     bullets = maxBullets;
    //     lastTimeShot = -1;
    // }
}

void Blaster::shoot(const std::vector<std::shared_ptr<Entity>>& shootingEntities, uint32_t xPos,
                    float time) {
    lastTimeShot = time;
    bullets--;
    bulletsShot++;
    std::cout << "[BLASTER] Shooting at " << xPos << std::endl;

    if (shootingEntities.empty())
        return;
    if (bullets > 0){
        for (auto& entity: shootingEntities) {
            entity->recvDamage(damage, time);
        }

    }
    std::cout << "[BLASTER] Bullets post shot: " << (int)bullets << std::endl;
}

void Blaster::reload() { bullets = maxBullets; }

bool Blaster::isEmpty() { return bullets == 0; }

bool Blaster::isLoaded() { return bullets == maxBullets; }

uint8_t Blaster::getBullets() { return bullets; }

uint8_t Blaster::getBulletsShot() { return bulletsShot; }

bool Blaster::shootTime(float time) {
    return lastTimeShot != -1 && time - lastTimeShot >= fireRate;
}

WeaponType Blaster::getWeaponType() { return WeaponType::BLASTER; }

float Blaster::getFireRate() { return fireRate; }

bool Blaster::cooldown(float time) {
    return (time - lastTimeShot) > fireRate;
}

uint8_t Blaster::getDamage() { return damage; }
