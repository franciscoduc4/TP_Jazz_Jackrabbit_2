#ifndef PLAYER_CHARACTER_H
#define PLAYER_CHARACTER_H

#include <cstdint>
#include <memory>
#include <vector>

#include "../../Common/Types/character.h"
#include "../../Common/Types/direction.h"
#include "states/state.h"
#include "states/idle.h"
#include "weapons/weapon.h"
#include "weapons/blaster.h"
#include "entity.h"

class GameMap;

class Character : public Entity {
private:
    GameMap& map;
    int16_t x;
    int16_t y;
    int16_t characterId;
    int16_t health;
    int16_t initialHealth;
    Move dir;
    int16_t maxMoves;
    int16_t timesRevived;
    int16_t maxRevived;

    std::unique_ptr<Weapon> currentWeapon = std::make_unique<Blaster>();
    std::unique_ptr<State> state = std::make_unique<IdleState>();

    Move direction = Move::RIGHT;
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
<<<<<<< Updated upstream
    Vector<int16_t> getPosition() override;
=======
    ~Character() = default;

    Vector<float> getPosition() override;
>>>>>>> Stashed changes
    int16_t getId() override;
    int16_t getMove() override;
    Vector<int16_t> getMapPosition() override;
    void recvDamage(uint16_t damage, float time) override;
    void setDir(Move dir);

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

    bool isAlive() const { return !isDead; }

    int16_t getHealth() { return health; }
<<<<<<< Updated upstream
    int16_t getDir() { return dir; }
    int16_t getX() { return x; }
=======
    Move getDir() { return dir; }
    int16_t getX() { return x; }
    int16_t getMatrixX() { return x / maxMoves; }
    int16_t getMatrixY() { return y / maxMoves; }
>>>>>>> Stashed changes
    int16_t getY() { return y; }
    int16_t getCharacterId() const { return characterId; }
    float getRespawnTime() const { return respawnTime; }
    bool characIsIntoxicated() { return isIntoxicated; }
    float getIntoxicatedTime() { return intoxicatedTime; }
<<<<<<< Updated upstream
=======
    std::vector<std::shared_ptr<Entity>> getTargets();
>>>>>>> Stashed changes

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
};

#endif // PLAYER_CHARACTER_H
