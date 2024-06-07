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
private:
    GameMap& gameMap;

    std::shared_ptr<Character> createJazz(int16_t characterId, Vector<int16_t> position);

    std::shared_ptr<Character> createSpaz(int16_t characterId, Vector<int16_t> position);

    std::shared_ptr<Character> createLori(int16_t characterId, Vector<int16_t> position);

    std::shared_ptr<Enemy> createWalker(int16_t enemyId, Vector<int16_t> position);

    std::shared_ptr<Enemy> createFlyer(int16_t enemyId, Vector<int16_t> position);

    std::shared_ptr<Enemy> createJumper(int16_t enemyId, Vector<int16_t> position);

public:
    EntityFactory(GameMap& gameMap);

    std::shared_ptr<Character> createCharacter(uint8_t characterId, CharacterType type,
                                               Vector<int16_t> position);

    std::shared_ptr<Enemy> createEnemy(uint8_t enemyId, EnemyType type, Vector<int16_t> position);
};


#endif  // ENTITY_FACTORY_H_
