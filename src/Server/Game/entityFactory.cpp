#include "entityFactory.h"

#include "characters/jazz.h"
#include "characters/lori.h"
#include "characters/spaz.h"
#include "enemies/Schwarzenguard.h"
#include "enemies/Turtle.h"
#include "enemies/Yellowmon.h"
#include "items/bullet.h"
#include "items/food.h"
#include "items/gem.h"
#include "items/goldCoin.h"
#include "items/poisonedFood.h"
#include "items/silverCoin.h"
#include "obstacles/column.h"
#include "obstacles/fullFloor.h"
#include "obstacles/leftLadder.h"
#include "obstacles/longPlatform.h"
#include "obstacles/rightLadder.h"
#include "obstacles/smallPlatform.h"

#include "gameMap.h"

EntityFactory::EntityFactory(GameMap& gameMap): gameMap(gameMap) {}

std::shared_ptr<Character> EntityFactory::createCharacter(uint8_t playerId, CharacterType type,
                                                          Vector<uint32_t> position, uint32_t width,
                                                          uint32_t height) {
    switch (type) {
        case CharacterType::JAZZ:
            return std::make_shared<Jazz>(gameMap, position, playerId, width, height);
        case CharacterType::SPAZ:
            return std::make_shared<Spaz>(gameMap, position, playerId, width, height);
        case CharacterType::LORI:
            return std::make_shared<Lori>(gameMap, position, playerId, width, height);
    }
    return nullptr;
}

std::shared_ptr<Enemy> EntityFactory::createEnemy(uint8_t enemyId, EnemyType type,
                                                  Vector<uint32_t> position, uint32_t width,
                                                  uint32_t height) {
    switch (type) {
        case EnemyType::TURTLE:
            return std::make_shared<Turtle>(gameMap, position, enemyId, width, height);
        case EnemyType::YELLOWMON:
            return std::make_shared<Yellowmon>(gameMap, position, enemyId, width, height);
        case EnemyType::SCHWARZENGUARD:
            return std::make_shared<Schwarzenguard>(gameMap, position, enemyId, width, height);
    }
    return nullptr;
}

std::shared_ptr<Item> EntityFactory::createItem(ItemType type, Vector<uint32_t> position,
                                                uint32_t width, uint32_t height) {
    switch (type) {
        case ItemType::FOOD:
            return std::make_shared<Food>(gameMap, position, width, height);
        case ItemType::GEM:
            return std::make_shared<Gem>(gameMap, position, width, height);
        case ItemType::SILVER_COIN:
            return std::make_shared<SilverCoin>(gameMap, position, width, height);
        case ItemType::GOLD_COIN:
            return std::make_shared<GoldCoin>(gameMap, position, width, height);
        case ItemType::POISONED_FOOD:
            return std::make_shared<PoisonedFood>(gameMap, position, width, height);
        case ItemType::BULLET:
            return std::make_shared<Bullet>(gameMap, position, width, height);
        default:
            return nullptr;
    }
}

std::shared_ptr<Obstacle> EntityFactory::createObstacle(ObstacleType type,
                                                        Vector<uint32_t> position, uint32_t width,
                                                        uint32_t height) {
    switch (type) {
        case ObstacleType::FULL_FLOOR:
            return std::make_shared<FullFloor>(gameMap, position, width, height);
        case ObstacleType::LEFT_LADDER:
            return std::make_shared<LeftLadder>(gameMap, position, width, height);
        case ObstacleType::LONG_PLATFORM:
            return std::make_shared<LongPlatform>(gameMap, position, width, height);
        case ObstacleType::RIGHT_LADDER:
            return std::make_shared<RightLadder>(gameMap, position, width, height);
        case ObstacleType::SMALL_PLATFORM:
            return std::make_shared<SmallPlatform>(gameMap, position, width, height);
        case ObstacleType::COLUMN:
            return std::make_shared<Column>(gameMap, position, width, height);
        default:
            return nullptr;
    }
    return nullptr;
}
