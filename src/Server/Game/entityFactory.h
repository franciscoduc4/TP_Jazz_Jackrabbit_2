#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

#include <memory>
#include <string>
#include "../../Common/vector.h"
#include "entity.h"
#include "characters/character.h"
#include "enemies/enemy.h"
#include "items/item.h"
#include "obstacles/obstacle.h"

class Character;
class Enemy;
class GameMap;
class Item;
class Obstacle;

class EntityFactory {
private:
    GameMap& gameMap;

    std::shared_ptr<Character> createJazz(uint8_t playerId, Vector<uint32_t> position);

    std::shared_ptr<Character> createSpaz(uint8_t playerId, Vector<uint32_t> position);

    std::shared_ptr<Character> createLori(uint8_t playerId, Vector<uint32_t> position);

    std::shared_ptr<Enemy> createWalker(uint8_t enemyId, Vector<uint32_t> position);

    std::shared_ptr<Enemy> createFlyer(uint8_t enemyId, Vector<uint32_t> position);

    std::shared_ptr<Enemy> createJumper(uint8_t enemyId, Vector<uint32_t> position);

public:
    EntityFactory(GameMap& gameMap);

    std::shared_ptr<Character> createCharacter(uint8_t playerId, CharacterType type,
                                               Vector<uint32_t> position);

    std::shared_ptr<Enemy> createEnemy(uint8_t enemyId, EnemyType type, Vector<uint32_t> position);

    std::shared_ptr<Item> createItem(ItemType type, Vector<uint32_t> position);

    std::shared_ptr<Obstacle> createObstacle(ObstacleType type, Vector<uint32_t> position);
};


#endif  // ENTITY_FACTORY_H_
