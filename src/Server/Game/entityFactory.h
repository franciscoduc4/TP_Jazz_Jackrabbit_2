#ifndef ENTITY_FACTORY_H_
#define ENTITY_FACTORY_H_

#include <cstdint>
#include <memory>
#include <vector>

#include "characters/jazz.h"
#include "characters/lori.h"
#include "characters/spaz.h"
#include "enemies/enemy.h"
#include "enemies/flyingEnemy.h"
#include "enemies/jumpingEnemy.h"
#include "enemies/walkingEnemy.h"

#include "gameMap.h"

class EntityFactory {
private:
    GameMap& gameMap;

    std::shared_ptr<Character> createJazz(int16_t characterId, Vector<int16_t> position) {
        return std::make_shared<Jazz>(gameMap, position, characterId);
    }
    std::shared_ptr<Character> createSpaz(int16_t characterId, Vector<int16_t> position) {
        return std::make_shared<Spaz>(gameMap, position, characterId);
    }
    std::shared_ptr<Character> createLori(int16_t characterId, Vector<int16_t> position) {
        return std::make_shared<Lori>(gameMap, position, characterId);
    }

    std::shared_ptr<Enemy> createWalker(int16_t enemyId, Vector<int16_t> position) {
        return std::make_shared<WalkingEnemy>(gameMap, position, enemyId);
    }
    std::shared_ptr<Enemy> createFlyer(int16_t enemyId, Vector<int16_t> position) {
        return std::make_shared<FlyingEnemy>(gameMap, position, enemyId);
    }
    std::shared_ptr<Enemy> createJumper(int16_t enemyId, Vector<int16_t> position) {
        return std::make_shared<JumpingEnemy>(gameMap, position, enemyId);
    }

public:
    EntityFactory(GameMap& gameMap): gameMap(gameMap) {}

    std::shared_ptr<Character> createCharacter(uint8_t characterId, CharacterType type,
                                               Vector<int16_t> position) {
        switch (type) {
            case CharacterType::JAZZ:
                return createJazz(characterId, position);
            case CharacterType::SPAZ:
                return createSpaz(characterId, position);
            case CharacterType::LORI:
                return createLori(characterId, position);
        }
        return nullptr;
    }

    std::shared_ptr<Enemy> createEnemy(uint8_t enemyId, EnemyType type, Vector<int16_t> position) {
        switch (type) {
            case EnemyType::WALKING_ENEMY:
                return createWalker(enemyId, position);
            case EnemyType::FLYING_ENEMY:
                return createFlyer(enemyId, position);
            case EnemyType::JUMPING_ENEMY:
                return createJumper(enemyId, position);
        }
        return nullptr;
    }
};


#endif  // ENTITY_FACTORY_H_
