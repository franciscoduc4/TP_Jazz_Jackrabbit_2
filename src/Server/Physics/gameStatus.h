#ifndef GAME_STATUS_H_H
#define GAME_STATUS_H_H


#include "character.h"
#include "enemy.h"
#include "collectible.h"
#include "platform.h"
#include "obstacle.h"
#include "vector.h"

class GameStatus {
private:
    std::vector<std::shared_ptr<Character>> characters; 
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Gem>> gems;
    std::vector<std::unique_ptr<Coin>> coins;
    std::vector<Projectile> projectiles;

    float deltaTime = 0.016f;

public:
    void update() {
        for (auto& character : characters) {
            character->update(deltaTime);
        }

        for (auto& enemy : enemies) {
            enemy->update(deltaTime);
        }

        for (auto& gem : gems) {
            gem->update(deltaTime);
        }

        for (auto& coin : coins) {
            coin->update(deltaTime);
        }
    }

    void addCharacter(std::shared_ptr<Character> character) {
        characters.push_back(character);
    }

    void addEnemy(std::unique_ptr<Enemy> enemy) {
        enemies.push_back(std::move(enemy));
    }

    void addGem(std::unique_ptr<Gem> gem) {
        gems.push_back(std::move(gem));
    }

    void addCoin(std::unique_ptr<Coin> coin) {
        coins.push_back(std::move(coin));
    }

    void addProjectile(Vector position, Vector velocity, int damage) {
        projectiles.emplace_back(position, velocity, damage);
    }

    std::vector<std::shared_ptr<Character>>& getCharacters() {
        return characters;
    }



};

#endif  // GAME_STATUS_H_H
