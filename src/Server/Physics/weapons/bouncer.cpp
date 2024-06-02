#include "bouncer.h"

Bouncer::Bouncer() :
    bullets(25),
    maxBullets(25),
    damage(20),
    fireRate(0.75),
    lastTimeShot(-1) {} // Todas las configuraciones deberían salir del YAML

void Bouncer::update(float time){
    if (lastTimeShot != -1 && time - lastTimeShot >= fireRate) {
        bullets = maxBullets;
        lastTimeShot = -1;
    }
}
void Bouncer::shoot(std::vector<Object*>& shootingObjects, int16_t xPos, float time){
    lastTimeShot = time;
    bullets--;
    bulletsShot++;

    if (shootingObjects.empty()) return;

    for (auto& object : shootingObjects) {
        object->recvDmg(damage, time);
    }
}

void Bouncer::reload(){
    bullets = maxBullets;
}

bool Bouncer::isEmpty(){
    return bullets == 0;
}

bool Bouncer::isLoaded(){
    return bullets == maxBullets;
}

int16_t Bouncer::getBullets(){
    return bullets;
}

int32_t Bouncer::getBulletsShot(){
    return bulletsShot;
}

bool Bouncer::shootTime(float time){
    return lastTimeShot != -1 && time - lastTimeShot >= fireRate;
}

WeaponType Bouncer::getWeaponType(){
    return WeaponType::BOUNCER;
}

float Bouncer::getFireRate(){
    return fireRate;
}
