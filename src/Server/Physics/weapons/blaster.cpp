#include "blaster.h"

Blaster::Blaster() :
    bullets(30),
    maxBullets(30),
    damage(10),
    fireRate(0.5),
    lastTimeShot(-1) {} //todas las settings deberian salir del YAML


void Blaster::update(float time){
        if (lastTimeShot != -1 && time - lastTimeShot >= fireRate) {
            bullets = maxBullets;
            lastTimeShot = -1;
        }        
    }

void Blaster::shoot(std::shared_ptr<Entity>& shootingEntities, int16_t xPos, float time){
    lastTimeShot = time;
    bullets--;
    bulletsShot++;

    if (shootingEntities.empty()) return;

    for (auto& object : shootingEntities) {
        object->recvDamage(damage, time);
    }
}

void Blaster::reload(){
    bullets = maxBullets;
}

bool Blaster::isEmpty(){
    return bullets == 0;
}

bool Blaster::isLoaded(){
    return bullets == maxBullets;
}

int16_t Blaster::getBullets(){
    return bullets;

}

int32_t Blaster::getBulletsShot(){
    return bulletsShot;
}

bool Blaster::shootTime(float time){
    return lastTimeShot != -1 && time - lastTimeShot >= fireRate;
}

WeaponType Blaster::getWeaponType(){
    return WeaponType::BLASTER;
}

float Blaster::getFireRate(){
    return fireRate;
}

