#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

#include <cstdint>
#include <memory>

#include "../../Common/Types/character.h"
#include "../../Common/Types/enemy.h"
#include "../../Common/vector.h"

class Character;
class Enemy;
class GameMap;

class EntityFactory {
public:
    EntityFactory(GameMap& gameMap);

    std::shared_ptr<Character> createCharacter(uint8_t playerId, CharacterType type, Vector<uint8_t> position);
    std::shared_ptr<Enemy> createEnemy(uint8_t enemyId, EnemyType type, Vector<uint8_t> position);
    // std::shared_ptr<Obstacle> createObstacle(const std::string& type, Vector<uint8_t> position);
    // std::shared_ptr<GoldCoin> createGoldCoin(Vector<uint8_t> position);
    // std::shared_ptr<SilverCoin> createSilverCoin(Vector<uint8_t> position);
    // std::shared_ptr<Gem> createGem(Vector<uint8_t> position);
    // std::shared_ptr<Tile> createTile(const std::string& type, Vector<uint8_t> position);

private:
    GameMap& gameMap;

    std::shared_ptr<Character> createJazz(uint8_t playerId, Vector<uint8_t> position);
    std::shared_ptr<Character> createSpaz(uint8_t playerId, Vector<uint8_t> position);
    std::shared_ptr<Character> createLori(uint8_t playerId, Vector<uint8_t> position);

    std::shared_ptr<Enemy> createWalker(uint8_t enemyId, Vector<uint8_t> position);
    std::shared_ptr<Enemy> createFlyer(uint8_t enemyId, Vector<uint8_t> position);
    std::shared_ptr<Enemy> createJumper(uint8_t enemyId, Vector<uint8_t> position);
};

#endif  // ENTITY_FACTORY_H_
