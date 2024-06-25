#ifndef ENEMY_H_
#define ENEMY_H_

#include <iostream>
#include <memory>
#include <vector>

#include "../../../Common/DTO/enemy.h"
#include "../../../Common/Types/enemy.h"
#include "../../../Common/vector.h"
#include "../characters/character.h"
#include "../entity.h"
#include "states/enemyState.h"

class GameMap;

class Enemy: public Entity {
protected:
    GameMap& gameMap;
    uint8_t dmg;
    std::unique_ptr<EnemyState> state;
    uint8_t viewDistance;
    uint8_t viewDistanceHit;
    uint8_t movesPerCell;
    uint8_t hitDistance;
    uint8_t speed;
    std::vector<uint8_t> walkProb;
    std::vector<uint8_t> jumpProb;
    std::vector<uint8_t> flyProb;
    uint32_t width;
    uint32_t height;

    Vector<uint32_t> initialPosition;
    uint32_t maxDistance;
    bool movingRight;


public:
    Enemy(GameMap& map, const Vector<uint32_t>& pos, uint8_t id, uint8_t health, Direction dir,
          uint8_t dmg, std::unique_ptr<EnemyState> initialState, uint8_t viewDistance,
          uint8_t viewDistanceHit, uint8_t movesPerCell, uint8_t hitDistance,
          std::vector<uint8_t> walkProb, std::vector<uint8_t> jumpProb,
          std::vector<uint8_t> flyProb, uint32_t width, uint32_t height);

    void update(const std::map<uint8_t, std::shared_ptr<Character>>& characters, float time);

    void update(double deltaTime) override;
    void moveCycle(float deltaTime);

    void recvDamage(uint8_t dmg, float time) override;

    void attack(std::vector<std::shared_ptr<Character>> characters, float time);

    void die(float time) override;

    std::unique_ptr<EnemyState>& getState();

    virtual EnemyType getEnemyType() const = 0;

    EnemyDTO getDTO() const;

    bool isDead() { return Entity::isEntityDead(); }

    virtual uint8_t getDamage() const = 0;

    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;

    std::shared_ptr<Character> getClosestCharacter(
            std::vector<std::shared_ptr<Character>> characters);
};

#endif  // ENEMY_H_
