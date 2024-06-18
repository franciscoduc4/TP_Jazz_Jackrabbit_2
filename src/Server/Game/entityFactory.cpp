#include "entityFactory.h"
#include "characters/jazz.h"
#include "characters/lori.h"
#include "characters/spaz.h"
#include "enemies/flyingEnemy.h"
#include "enemies/jumpingEnemy.h"
#include "enemies/walkingEnemy.h"

EntityFactory::EntityFactory(GameMap& gameMap): gameMap(gameMap) {}

std::shared_ptr<Character> EntityFactory::createCharacter(uint8_t playerId, CharacterType type,
                                                          Vector<uint8_t> position) {
    switch (type) {
        case CharacterType::JAZZ:
            return createJazz(playerId, position);
        case CharacterType::SPAZ:
            return createSpaz(playerId, position);
        case CharacterType::LORI:
            return createLori(playerId, position);
    }
    return nullptr;
}

std::shared_ptr<Enemy> EntityFactory::createEnemy(uint8_t enemyId, EnemyType type,
                                                  Vector<uint8_t> position) {
    switch (type) {
        case EnemyType::TURTLE:
            return createWalker(enemyId, position);
        case EnemyType::YELLOWMON:
            return createFlyer(enemyId, position);
        case EnemyType::SCHWARZENGUARD:
            return createJumper(enemyId, position);
    }
    return nullptr;
}

// std::shared_ptr<Obstacle> EntityFactory::createObstacle(const std::string& type, Vector<uint8_t> position) {
//     return std::make_shared<Obstacle>(type, position);
// }

// std::shared_ptr<GoldCoin> EntityFactory::createGoldCoin(Vector<uint8_t> position) {
//     return std::make_shared<GoldCoin>(gameMap, position);
// }

// std::shared_ptr<SilverCoin> EntityFactory::createSilverCoin(Vector<uint8_t> position) {
//     return std::make_shared<SilverCoin>(gameMap, position);
// }

// std::shared_ptr<Gem> EntityFactory::createGem(Vector<uint8_t> position) {
//     return std::make_shared<Gem>(gameMap, position);
// }

// std::shared_ptr<Tile> EntityFactory::createTile(const std::string& type, Vector<uint8_t> position) {
//     return std::make_shared<Tile>(type, position);
// }

std::shared_ptr<Character> EntityFactory::createJazz(uint8_t playerId, Vector<uint8_t> position) {
    return std::make_shared<Jazz>(gameMap, position, playerId);
}

std::shared_ptr<Character> EntityFactory::createSpaz(uint8_t playerId, Vector<uint8_t> position) {
    return std::make_shared<Spaz>(gameMap, position, playerId);
}

std::shared_ptr<Character> EntityFactory::createLori(uint8_t playerId, Vector<uint8_t> position) {
    return std::make_shared<Lori>(gameMap, position, playerId);
}

std::shared_ptr<Enemy> EntityFactory::createWalker(uint8_t enemyId, Vector<uint8_t> position) {
    return std::make_shared<WalkingEnemy>(gameMap, position, enemyId);
}

std::shared_ptr<Enemy> EntityFactory::createFlyer(uint8_t enemyId, Vector<uint8_t> position) {
    return std::make_shared<FlyingEnemy>(gameMap, position, enemyId);
}

std::shared_ptr<Enemy> EntityFactory::createJumper(uint8_t enemyId, Vector<uint8_t> position) {
    return std::make_shared<JumpingEnemy>(gameMap, position, enemyId);
}