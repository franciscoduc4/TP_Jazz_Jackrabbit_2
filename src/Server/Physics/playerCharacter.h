#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include <cstdint>
#include <memory>
#include <vector>

#include "../../Common/Types/character.h"
#include "../../Common/Types/direction.h"
#include "states/idle.h"
#include "states/state.h"
#include "weapons/blaster.h"
#include "weapons/bouncer.h"
#include "weapons/freezer.h"
#include "weapons/rfMissile.h"
#include "weapons/weapon.h"

#include "entity.h"

class GameMap;

class Character: public Entity {
private:
    GameMap& map;
    int16_t x;
    int16_t y;
    int16_t characterId;
    int16_t health;
    int16_t initialHealth;
    Direction dir;
    int16_t maxMoves;
    int16_t timesRevived;
    int16_t maxRevived;

    std::shared_ptr<Weapon> currentWeapon = std::make_unique<Blaster>();
    std::unique_ptr<State> state = std::make_unique<IdleState>();

    Direction direction = Direction::RIGHT;
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
    Vector<int16_t> getPosition() override;
    int16_t getId() override;
    Vector<int16_t> getMapPosition() override;
    void recvDamage(uint16_t damage, float time) override;
    void setDir(Direction dir);

    void update(float time);
    void shoot(float time);

    void moveRight(float time);
    void sprintRight(float time);
    void moveLeft(float time);
    void sprintLeft(float time);
    void moveUp(float time);
    void moveDown(float time);

    virtual void specialAttack(float time) = 0;

    void becomeIntoxicated(float duration);
    void die(float respawnTime);
    void revive(float time);

    void heal(uint16_t amount);

    bool isAlive() const;

    int16_t getHealth() const;
    Direction getDir() const;
    int16_t getX() const;
    int16_t getMatrixX() const;
    int16_t getMatrixY() const;
    int16_t getY() const;
    int16_t getCharacterId() const;
    float getRespawnTime() const;
    bool characIsIntoxicated() const;
    float getIntoxicatedTime() const;
    std::vector<std::shared_ptr<Entity>> getTargets();

    void moveRight();
    void moveDown();
    void moveLeft();
    void moveUp();
    void switchWeapon(WeaponType type);

    void interact(std::shared_ptr<Entity>& other) override;
};
#endif  // PLAYER_CHARACTER_H
