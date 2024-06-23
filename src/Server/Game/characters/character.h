#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include <cstdint>
#include <memory>
#include <vector>
#include "bullet.h"
#include "../../../Common/Config/ServerConfig.h"
#include "../../../Common/DTO/player.h"
#include "../../../Common/Types/character.h"
#include "../../../Common/Types/direction.h"
#include "../entity.h"
#include "../items/item.h"
#include "../weapons/blaster.h"
#include "../weapons/bouncer.h"
#include "../weapons/freezer.h"
#include "../weapons/rfMissile.h"
#include "../weapons/weapon.h"
#include "states/dead.h"
#include "states/idle.h"
#include "states/intoxicated.h"
#include "states/jumping.h"
#include "states/moving.h"
#include "states/shooting.h"
#include "states/specialAttack.h"
#include "states/state.h"

class GameMap;
class Enemy;
class Obstacle;

class Character: public Entity, public std::enable_shared_from_this<Character> {
protected:
    CharacterType type;
    GameMap& gameMap;

    uint8_t maxHealth;
    float reviveTime;
    uint8_t maxRevived;
    uint8_t movesPerCell;
    uint8_t timesRevived;

    float respawnTime;
    float damageTime;
    float intoxicatedTime;
    float shootCooldownTime;

    Vector<float> currentSpeed;
    Vector<float> currentAcceleration;

    float verticalSpeed;
    float sprintSpeed;
    float horizontalSpeed;
    float jumpHeight;

    std::unique_ptr<Weapon> currentWeapon;
    std::unique_ptr<State> state;

    bool jumping = false;
    bool onGround = false;

    bool isIntoxicated = false;
    float shootCooldown = 0.0f;

    float jumpStartTime = 0.0f;
    float jumpDuration = 0.5f;
    uint8_t initialYJump = 0;

    uint32_t width;
    uint32_t height;

public:
    Character(GameMap& gameMap, Vector<uint32_t> pos, uint8_t playerId, CharacterType type,
              float horizontalSpeed, float sprintSpeed, float verticalSpeed, float jumpHeight,
              float shootCooldownTime, uint32_t width, uint32_t height);

    void idle(float time);
    void recvDamage(uint8_t damage, float time) override;
    void update(float time);
    void shoot(float time);

    bool isPointInTriangle(const Vector<uint32_t>& p, const Vector<uint32_t>& v1, 
    const Vector<uint32_t>& v2, const Vector<uint32_t>& v3);
    void update(double deltaTime);
    void handleCollision(std::shared_ptr<Enemy> enemy);
    void handleObstacleCollision(std::shared_ptr<Obstacle> obstacle);
    void handleLadderCollision(std::shared_ptr<Obstacle> obstacle);

    void moveRight(double time);
    void sprintRight(float time);
    void moveLeft(double time);
    void sprintLeft(float time);
    void moveUp(float time);
    void moveDown(float time);
    void jump(float time);

    virtual void specialAttack(float time) = 0;

    void becomeIntoxicated(float duration);
    void die(float respawnTime) override;
    void revive(float time);

    void collectItem(const std::shared_ptr<Item>& item);
    void heal(uint8_t amount);

    std::vector<std::shared_ptr<Entity>> getTargets();
    void interact(std::shared_ptr<Entity>& other);
    void switchWeapon(WeaponType type);

    void moveRight();
    void moveLeft();
    void moveDown();
    void moveUp();


    bool characIsIntoxicated() const;
    float getIntoxicatedTime() const;

    WeaponType getCurrentWeaponType();

    CharacterType getCharacterType();

    PlayerDTO getDTO() const;

    bool isJumping() { return jumping; }
    bool hasLanded();
    bool isOnGround() const;

    uint32_t getWidth() const;
    uint32_t getHeight() const;

    void setOnGround(bool onGround);
};

#endif  // PLAYER_CHARACTER_H
