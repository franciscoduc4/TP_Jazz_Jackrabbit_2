#ifndef GAME_STATUS_H_H
#define GAME_STATUS_H_H

#include <cstring>
#include <map>
#include <mutex>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include <memory>
#include "character.h"
#include "enemy.h"
#include "game.h"
#include "player.h"
#include <utility>

struct Gem {
    int x;
    int y;
    int points;
};

struct Coin {
    int x;
    int y;
    int points;
};

struct GameStatus {
    std::vector<std::shared_ptr<Character>> characters;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Gem>> gems;
    std::vector<std::shared_ptr<Coin>> coins;

    void addCharacter(std::shared_ptr<Character> character) {
        characters.push_back(std::move(character));
    }

    void handleAction(const GameTypes::Action& action) {
        for (auto& character: characters) {
            if (character->getId() == action.id) {
                character->handleAction(action);
                return;
            }
        }
    }
    
    std::string snapshot() const {
        std::string buffer;

        uint32_t characterCount = htonl(characters.size());
        buffer.append(reinterpret_cast<const char*>(&characterCount), sizeof(characterCount));
        for (const auto& character: characters) {
            serializeString(character->getName(), buffer);
            serializeString(character->getState(), buffer);
            serializeInt(character->getX(), buffer);
            serializeInt(character->getY(), buffer);
            serializeInt(character->getHealth(), buffer);
        }

        uint32_t enemyCount = htonl(enemies.size());
        buffer.append(reinterpret_cast<const char*>(&enemyCount), sizeof(enemyCount));
        for (const auto& enemy: enemies) {
            serializeString(enemy->getType(), buffer);
            serializeInt(enemy->getX(), buffer);
            serializeInt(enemy->getY(), buffer);
            serializeInt(enemy->getHealth(), buffer);
            serializeInt(enemy->getDamage(), buffer);
            serializeInt(enemy->getPoints(), buffer);
            serializeFloat(enemy->getRespawnTime(), buffer);
            serializeFloat(enemy->getDropProbability(), buffer);
        }

        uint32_t gemCount = htonl(gems.size());
        buffer.append(reinterpret_cast<const char*>(&gemCount), sizeof(gemCount));
        for (const auto& gem: gems) {
            serializeInt(gem->x, buffer);
            serializeInt(gem->y, buffer);
            serializeInt(gem->points, buffer);
        }

        uint32_t coinCount = htonl(coins.size());
        buffer.append(reinterpret_cast<const char*>(&coinCount), sizeof(coinCount));
        for (const auto& coin: coins) {
            serializeInt(coin->x, buffer);
            serializeInt(coin->y, buffer);
            serializeInt(coin->points, buffer);
        }

        return buffer;
    }

private:
    void serializeInt(int32_t value, std::string& buffer) const {
        value = htonl(value);
        buffer.append(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    void serializeFloat(float value, std::string& buffer) const {
        int32_t ivalue;
        std::memcpy(&ivalue, &value, sizeof(value));
        ivalue = htonl(ivalue);
        buffer.append(reinterpret_cast<const char*>(&ivalue), sizeof(ivalue));
    }

    void serializeString(const std::string& value, std::string& buffer) const {
        uint32_t size = htonl(value.size());
        buffer.append(reinterpret_cast<const char*>(&size), sizeof(size));
        buffer.append(value);
    }
};

#endif  // GAME_STATUS_H_H
