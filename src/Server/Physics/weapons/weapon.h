#ifndef WEAPON_H_
#define WEAPON_H_

#include <vector>
#include <iostream>
#include "../../../Common/Types/character.h"
#include "../../../Common/Types/weapon.h"
#include "../object.h"

class GameMap;
class State;
class Object;

class Weapon {
    public:
    virtual void update(float time) = 0;

    virtual void shoot(std::vector<Object*>& shootingObjects, int16_t xPos, float time) = 0;
    virtual void reload() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isLoaded() = 0;
    virtual int16_t getBullets() = 0;
    virtual int32_t getBulletsShot() = 0;
    virtual bool shootTime(float time)  = 0;
    virtual float getFireRate() = 0;
    virtual WeaponType getWeaponType() = 0;


    // virtual LoriSpecialAttack* getLoriSpecialAttack() = 0;
    // virtual JazzSpecialAttack* getLoriSpecialAttack() = 0;
    // virtual SpazSpecialAttack* getLoriSpecialAttack() = 0;


    virtual ~Weapon() {}

}

#endif // WEAPON_H_

