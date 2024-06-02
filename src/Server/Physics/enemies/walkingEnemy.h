#ifndef WALKING_ENEMY_H
#define WALKING_ENEMY_H

#include "enemy.h"
#include <memory>
#include <vector>
#include "../enemyStates/enemyState.h"
#include "../enemyStates/enemyIdle.h"

class WalkingEnemy : public Entity, public Enemy {
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
        WalkingEnemy(int16_t x, int16_t y, int16_t id, GameMap& map, int16_t health,
        int16_t dmg);

        void update(std::vector<Character*> characters, float time) override;

        void receiveDmg(int16_t dmg, float time) override;

        void attack(std::vector<Character*> characters, float time) override;

        void die(float time) override;

        void setDir(int16_t dir) override;

        int16_t getX() override;
        int16_t getY() override;
        int16_t getMatrixX() override;
        int16_t getMatrixY() override;
        int16_t getId() override;
        int16_t getHealth() override;

        int16_t getDistanceToCharacter(Character* character);
        int16_t getXDistanceToCharacter(Character* character);
        int16_t getYDistanceToCharacter(Character* character);
        Character* getClosestCharacter(std::vector<Character*> characters);

        EnemyType getEnemyType() override;

        ~WalkingEnemy();
};
