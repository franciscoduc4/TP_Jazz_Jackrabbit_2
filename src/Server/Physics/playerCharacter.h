#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "object.h"
#include "states/state.h"
#include "../../Common/Types/character.h"
#include "weapons/weapon.h"
#include <cstdint>
#include <memory>

class GameMap;
class Weapon;

class Character : public Object {
private:
    GameMap& map;
    int16_t x;
    int16_t y;
    int16_t characterId;
    int16_t health;
    int16_t initialHealth;
    int16_t dir;
    int16_t maxMoves;
    int16_t timesRevived;
    int16_t maxRevived;

    Weapon* currentWeapon = nullptr;
    State* state = new IdleState();

    bool isDead = false;
    bool isIntoxicated = false;
    float intoxicatedTime = 0.0f;
    float respawnTime = 0.0f;

    float shootCooldown = 0.0f;
    float shootCooldownTime = 1.0f;  

    float speed = 100.0f;
    float sprintSpeed = 200.0f;
    float jumpHeight = 50.0f;

public:
    Character(GameMap& map, int16_t x, int16_t y, int16_t characterId, CharacterType type);
    int16_t getX();
    int16_t getY();
    int16_t getId();
    int16_t getMapX();
    int16_t getMapY();

    void recvDmg(uint16_t dmg, float time);
    void setDir(int16_t dir);

    void update(float time);
    void shoot(float time);

    void moveToRight(float time);
    void sprintToRight(float time);
    void moveToLeft(float time);
    void sprintToLeft(float time);
    void moveToUp(float time);
    void moveToDown(float time);


    virtual void specialAttack(float time) = 0;

    void becomeIntoxicated(float duration);
    void die(float respawnTime);
    void revive(float time);

    void heal(uint16_t amount);

    bool isAlive() const { return !isDead; }

    int16_t getHealth() const { return health; }
    int16_t getDir() const { return dir; }
    int16_t getCharacterId() const { return characterId; }
    float getRespawnTime() const { return respawnTime; }
    bool characIsIntoxicated() const { return isIntoxicated; }
    float getIntoxicatedTime() const { return intoxicatedTime; }

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
};

#endif // PLAYER_CHARACTER_H
