#ifndef ENEMY_H_
#define ENEMY_H_

#include <iostream>
#include <memory>
#include <vector>

#include "../../../Common/Types/enemy.h"
#include "../../../Common/vector.h"
#include "../characters/character.h"
#include "../entity.h"
#include "states/enemyState.h"

class GameMap;

class Enemy: public Entity {
protected:
    GameMap& gameMap;
    uint16_t dmg;
    std::unique_ptr<EnemyState> state;
    int16_t viewDistance;
    int16_t viewDistanceHit;
    int16_t movesPerCell;
    int16_t hitDistance;
    std::vector<int16_t> walkProb;
    std::vector<int16_t> jumpProb;
    std::vector<int16_t> flyProb;

public:
    Enemy(GameMap& map, Vector<int16_t> pos, int16_t id, int16_t health, Direction dir,
          uint16_t dmg, std::unique_ptr<EnemyState> initialState, int16_t viewDistance,
          int16_t viewDistanceHit, int16_t movesPerCell, int16_t hitDistance,
          std::vector<int16_t> walkProb, std::vector<int16_t> jumpProb,
          std::vector<int16_t> flyProb);

    void update(std::vector<std::shared_ptr<Character>> characters, float time);

    void recvDamage(uint16_t dmg, float time) override;

    void attack(std::vector<std::shared_ptr<Character>> characters, float time);

    void die(float time) override;

    std::unique_ptr<EnemyState>& getState();

    virtual EnemyType getEnemyType() = 0;

    std::shared_ptr<Character> getClosestCharacter(
            std::vector<std::shared_ptr<Character>> characters);
};

#endif  // ENEMY_H_
