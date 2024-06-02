#include "freezer.h"

Freezer::Freezer() :
    bullets(20),
    maxBullets(20),
    damage(15),
    fireRate(1.0),
    lastTimeShot(-1) {} // Todas las configuraciones deberían salir del YAML

void Freezer::update(float time){
    if (lastTimeShot != -1 && time - lastTimeShot >= fireRate) {
        bullets = maxBullets;
        lastTimeShot = -1;
    }
}

void Freezer::shoot(std::vector<Object*>& shootingObjects, int16_t xPos, float time){
    lastTimeShot = time;
    bullets--;
    bulletsShot++;

    if (shootingObjects.empty()) return;

    for (auto& object : shootingObjects) {
        object->recvDmg(damage, time);
    }
}

void Freezer::reload(){
    bullets = maxBullets;
}

bool Freezer::isEmpty(){
    return bullets == 0;
}

bool Freezer::isLoaded(){
    return bullets == maxBullets;
}

int16_t Freezer::getBullets(){
    return bullets;
}

int32_t Freezer::getBulletsShot(){
    return bulletsShot;
}

bool Freezer::shootTime(float time){
    return lastTimeShot != -1 && time - lastTimeShot >= fireRate;
}

WeaponType Freezer::getWeaponType(){
    return WeaponType::FREEZER;
}

float Freezer::getFireRate(){
    return fireRate;
}
