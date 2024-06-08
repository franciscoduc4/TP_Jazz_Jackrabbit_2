#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include <cstdint>
#include <memory>
#include <vector>

#include "../../../Common/Config/ServerConfig.h"
#include "../../../Common/Types/character.h"
#include "../../../Common/Types/direction.h"
#include "../entity.h"
#include "../weapons/blaster.h"
#include "../weapons/bouncer.h"
#include "../weapons/freezer.h"
#include "../weapons/rfMissile.h"
#include "../weapons/weapon.h"
#include "states/dead.h"
#include "states/idle.h"
#include "states/intoxicated.h"
#include "states/jumping.h"
#include "states/shooting.h"
#include "states/specialAttack.h"
#include "states/state.h"

class GameMap;

class Character: public Entity {
protected:
    CharacterType type;
    GameMap& gameMap;

    int16_t maxHealth;
    float reviveTime;
    int16_t maxRevived;
    int16_t movesPerCell;
    int16_t timesRevived;

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

    bool isIntoxicated = false;
    float shootCooldown = 0.0f;

public:
    Character(GameMap& gameMap, Vector<int16_t> pos, int16_t characterId, CharacterType type,
              float horizontalSpeed, float sprintSpeed, float verticalSpeed, float jumpHeight,
              float shootCooldownTime);

    void recvDamage(uint16_t damage, float time) override;
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
    void die(float respawnTime) override;
    void revive(float time);

    void heal(uint16_t amount);

    std::vector<std::shared_ptr<Entity>> getTargets();
    void interact(std::shared_ptr<Entity>& other);
    void switchWeapon(WeaponType type);

    void moveRight();
    void moveDown();
    void moveLeft();
    void moveUp();

    bool characIsIntoxicated() const;
    float getIntoxicatedTime() const;

    WeaponType getCurrentWeaponType();

    CharacterType getCharacterType();

    void heal(int32_t healQnt);
};

#endif  // PLAYER_CHARACTER_H
