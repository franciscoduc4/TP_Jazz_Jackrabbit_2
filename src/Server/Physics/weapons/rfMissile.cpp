#include "rfMissile.h"

RFMissile::RFMissile() :
    bullets(10),
    maxBullets(10),
    damage(30),
    fireRate(1.5),
    lastTimeShot(-1) {} // Todas las configuraciones deberían salir del YAML

void RFMissile::update(float time){
    if (lastTimeShot != -1 && time - lastTimeShot >= fireRate) {
        bullets = maxBullets;
        lastTimeShot = -1;
    }
}

void RFMissile::shoot(std::shared_ptr<Entity>& shootingEntities, int16_t xPos, float time){
    lastTimeShot = time;
    bullets--;
    bulletsShot++;

    if (shootingEntities.empty()) return;

    for (auto& object : shootingEntities) {
        object->recvDamage(damage, time);
    }
}

void RFMissile::reload(){
    bullets = maxBullets;
}

bool RFMissile::isEmpty(){
    return bullets == 0;
}

bool RFMissile::isLoaded(){
    return bullets == maxBullets;
}

int16_t RFMissile::getBullets(){
    return bullets;
}

int32_t RFMissile::getBulletsShot(){
    return bulletsShot;
}

bool RFMissile::shootTime(float time){
    return lastTimeShot != -1 && time - lastTimeShot >= fireRate;
}

WeaponType RFMissile::getWeaponType(){
    return WeaponType::RFMISSILE;
}

float RFMissile::getFireRate(){
    return fireRate;
}
