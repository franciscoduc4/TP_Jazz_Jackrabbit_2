#ifndef GAME_STATUS_H_H
#define GAME_STATUS_H_H

#include <vector>
#include <utility>
#include "../../Common/Models/vector.h"
#include <string>
#include "character.h"
#include "collectible.h"
#include "enemy.h"
#include "obstacle.h"
#include "platform.h"
#include "projectile.h"
#include <memory> 


class GameStatus {
private:
    std::vector<std::shared_ptr<Character>> characters;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<std::unique_ptr<Gem>> gems;
    std::vector<std::unique_ptr<Coin>> coins;
    std::vector<std::unique_ptr<Projectile>> projectiles;
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    std::vector<std::unique_ptr<Platform>> platforms;

    float deltaTime = 0.016f;

public:
    void addCharacter(std::shared_ptr<Character> character) { characters.push_back(character); }

    void addEnemy(std::unique_ptr<Enemy> enemy) { enemies.push_back(std::move(enemy)); }

    void addGem(std::unique_ptr<Gem> gem) { gems.push_back(std::move(gem)); }

    void addCoin(std::unique_ptr<Coin> coin) { coins.push_back(std::move(coin)); }

    void addProjectile(std::unique_ptr<Projectile> projectile) {
        projectiles.emplace_back(std::move(projectile));
    }

    void addObstacle(std::unique_ptr<Obstacle> obstacle) {
        obstacles.push_back(std::move(obstacle));
    }

    void addPlatform(std::unique_ptr<Platform> platform) {
        platforms.push_back(std::move(platform));
    }

    std::shared_ptr<Character> getCharacter(int id) {
        for (const auto& character: characters) {
            if (character->getId() == id) {
                return character;
            }
        }
        return nullptr;
    }

    std::vector<std::shared_ptr<Character>>& getCharacters() { return characters; }

    std::vector<std::unique_ptr<Enemy>>& getEnemies() { return enemies; }

    std::vector<std::unique_ptr<Gem>>& getGems() { return gems; }

    std::vector<std::unique_ptr<Coin>>& getCoins() { return coins; }

    std::vector<std::unique_ptr<Projectile>>& getProjectiles() { return projectiles; }

    std::vector<std::unique_ptr<Obstacle>>& getObstacles() { return obstacles; }

    std::vector<std::unique_ptr<Platform>>& getPlatforms() { return platforms; }

    std::string serialize() const {
        std::string serialized = "GameStatus\n";
        for (const auto& character: characters) {
            serialized += character->serialize() + "\n";
        }
        for (const auto& enemy: enemies) {
            serialized += enemy->serialize() + "\n";
        }
        for (const auto& gem: gems) {
            serialized += gem->serialize() + "\n";
        }
        for (const auto& coin: coins) {
            serialized += coin->serialize() + "\n";
        }
        for (const auto& projectile: projectiles) {
            serialized += projectile->serialize() + "\n";
        }
        for (const auto& obstacle: obstacles) {
            serialized += obstacle->serialize() + "\n";
        }
        for (const auto& platform: platforms) {
            serialized += platform->serialize() + "\n";
        }
        return serialized;
    }
};

#endif  // GAME_STATUS_H_H
