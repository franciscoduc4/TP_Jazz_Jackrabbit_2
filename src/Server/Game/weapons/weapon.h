#ifndef WEAPON_H_
#define WEAPON_H_

#include <iostream>
#include <memory>
#include <vector>

#include "../../../Common/DTO/weapon.h"
#include "../../../Common/Types/character.h"
#include "../../../Common/Types/weapon.h"
#include "../entity.h"

class GameMap;
class State;
class Entity;

class Weapon {
public:
    virtual void update(float time) = 0;

    virtual void shoot(std::vector<std::shared_ptr<Entity>>& shootingEntities, uint32_t xPos,
                       float time) = 0;
    virtual void reload() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isLoaded() = 0;
    virtual uint8_t getBullets() = 0;
    virtual uint8_t getBulletsShot() = 0;
    virtual bool shootTime(float time) = 0;
    virtual float getFireRate() = 0;
    virtual WeaponType getWeaponType() = 0;
    virtual bool cooldown(float time) = 0;
    virtual uint32_t getDamage() = 0;


    // virtual LoriSpecialAttack* getLoriSpecialAttack() = 0;
    // virtual JazzSpecialAttack* getLoriSpecialAttack() = 0;
    // virtual SpazSpecialAttack* getLoriSpecialAttack() = 0;


    virtual ~Weapon() {}
};

#endif  // WEAPON_H_
