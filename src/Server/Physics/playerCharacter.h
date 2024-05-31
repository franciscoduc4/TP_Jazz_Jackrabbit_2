#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include "object.h"
#include "states/state.h"
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
    int16_t dir;
    std::unique_ptr<Weapon> currentWeapon;
    std::unique_ptr<State> state;

    bool isDead = false;
    bool isIntoxicated = false;
    float intoxicatedTime = 0.0f;
    float respawnTime = 0.0f;

    float shootCooldown = 0.0f;
    float shootCooldownTime = 1.0f;  // Tiempo entre disparos

    float speed = 100.0f;
    float sprintSpeed = 200.0f;
    float jumpHeight = 50.0f;

public:
    Character(GameMap& map, int16_t characterId, int16_t initialHealth)
        : map(map), characterId(characterId), health(initialHealth), x(0), y(0), dir(1),
          state(new IdleState()) {}

    int16_t getX() override { return x; }
    int16_t getY() override { return y; }
    int16_t getId() override { return characterId; }
    void recvDmg(uint16_t dmg, float time) override;
    void setDir(int16_t dir) override { this->dir = dir; }

    void update(float time);
    void reload(float time);
    void shoot(float time);
    void moveToRight(float time);
    void sprintToRight(float time);
    void moveToLeft(float time);
    void sprintToLeft(float time);
    void jump(float time);

    // Acciones especiales
    virtual void specialAttack(float time) = 0;

    // Estados
    void becomeIntoxicated(float duration);
    void die(float respawnTime);

    // Gestión de salud
    void heal(uint16_t amount);

    // Verificación de estados
    bool isAlive() const { return !isDead; }

    // Getters
    int16_t getHealth() const { return health; }
    int16_t getDir() const { return dir; }
    int16_t getCharacterId() const { return characterId; }
    float getRespawnTime() const { return respawnTime; }
    bool isIntoxicated() const { return isIntoxicated; }
    float getIntoxicatedTime() const { return intoxicatedTime; }
};

#endif // PLAYER_CHARACTER_H
