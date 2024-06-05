#ifndef WALKING_ENEMY_H
#define WALKING_ENEMY_H

#include <memory>
#include <vector>

#include "../enemyStates/enemyIdle.h"
#include "../enemyStates/enemyState.h"

#include "enemy.h"

class WalkingEnemy: public Enemy {
private:
    int16_t movesPerCell;
    int16_t x;
    int16_t y;
    int16_t id;
    GameMap& map;
    int16_t health;
    int16_t dmg;
    int16_t hitDistance;
    int16_t hitDistanceY;
    int16_t viewDistance;
    int16_t viewDistanceHit;
    std::vector<int16_t> walkProb;
    std::vector<int16_t> flyProb;
    std::vector<int16_t> jumpProb;
    bool isDead = false;
    int16_t dir = -1;
    std::unique_ptr<EnemyState> state = std::make_unique<EnemyIdle>();

public:
    WalkingEnemy(int16_t x, int16_t y, int16_t id, GameMap& map, int16_t health, int16_t dmg);

    void update(std::vector<std::shared_ptr<Character>> characters, float time) override;

    void receiveDmg(int16_t dmg, float time) override;

    void attack(std::vector<std::shared_ptr<Character>>, float time) override;

    void die(float time) override;

    void setDir(int16_t dir) override;

    int16_t getX() override;
    int16_t getY() override;
    int16_t getMatrixX() override;
    int16_t getMatrixY() override;
    int16_t getId() override;
    int16_t getHealth() override;

    int16_t getDistanceToCharacter(std::shared_ptr<Character> character);
    int16_t getXDistanceToCharacter(std::shared_ptr<Character> character);
    int16_t getYDistanceToCharacter(std::shared_ptr<Character> character);
    std::shared_ptr<Character> getClosestCharacter(
            std::vector<std::shared_ptr<Character>> characters);

    EnemyType getEnemyType() override;
};

#endif  // WALKING_ENEMY_H
