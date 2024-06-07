#include "entityFactory.h"

#include "characters/jazz.h"
#include "characters/lori.h"
#include "characters/spaz.h"
#include "enemies/flyingEnemy.h"
#include "enemies/jumpingEnemy.h"
#include "enemies/walkingEnemy.h"

#include "gameMap.h"

EntityFactory::EntityFactory(GameMap& gameMap): gameMap(gameMap) {}

std::shared_ptr<Character> EntityFactory::createCharacter(uint8_t characterId, CharacterType type,
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

std::shared_ptr<Enemy> EntityFactory::createEnemy(uint8_t enemyId, EnemyType type,
                                                  Vector<int16_t> position) {
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

std::shared_ptr<Character> EntityFactory::createJazz(int16_t characterId,
                                                     Vector<int16_t> position) {
    return std::make_shared<Jazz>(gameMap, position, characterId);
}

std::shared_ptr<Character> EntityFactory::createSpaz(int16_t characterId,
                                                     Vector<int16_t> position) {
    return std::make_shared<Spaz>(gameMap, position, characterId);
}

std::shared_ptr<Character> EntityFactory::createLori(int16_t characterId,
                                                     Vector<int16_t> position) {
    return std::make_shared<Lori>(gameMap, position, characterId);
}

std::shared_ptr<Enemy> EntityFactory::createWalker(int16_t enemyId, Vector<int16_t> position) {
    return std::make_shared<WalkingEnemy>(gameMap, position, enemyId);
}

std::shared_ptr<Enemy> EntityFactory::createFlyer(int16_t enemyId, Vector<int16_t> position) {
    return std::make_shared<FlyingEnemy>(gameMap, position, enemyId);
}

std::shared_ptr<Enemy> EntityFactory::createJumper(int16_t enemyId, Vector<int16_t> position) {
    return std::make_shared<JumpingEnemy>(gameMap, position, enemyId);
}
