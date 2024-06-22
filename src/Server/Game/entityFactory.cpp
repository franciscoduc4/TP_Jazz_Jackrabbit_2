#include "entityFactory.h"
#include "characters/jazz.h"
#include "characters/lori.h"
#include "characters/spaz.h"
#include "enemies/flyingEnemy.h"
#include "enemies/jumpingEnemy.h"
#include "enemies/walkingEnemy.h"
#include "items/food.h"
#include "items/gem.h"
#include "items/goldCoin.h"
#include "items/silverCoin.h"
#include "obstacles/fullFloor.h"
#include "obstacles/leftLadder.h"
#include "obstacles/longPlatform.h"
#include "obstacles/rightLadder.h"
#include "obstacles/smallPlatform.h"
#include "obstacles/column.h"
#include "gameMap.h"

EntityFactory::EntityFactory(GameMap& gameMap) : gameMap(gameMap) {}

std::shared_ptr<Character> EntityFactory::createCharacter(uint8_t playerId, CharacterType type, Vector<uint32_t> position) {
    switch (type) {
        case CharacterType::JAZZ:
            return std::make_shared<Jazz>(gameMap, position, playerId);
        case CharacterType::SPAZ:
            return std::make_shared<Spaz>(gameMap, position, playerId);
        case CharacterType::LORI:
            return std::make_shared<Lori>(gameMap, position, playerId);
    }
    return nullptr;
}

std::shared_ptr<Enemy> EntityFactory::createEnemy(uint8_t enemyId, EnemyType type, Vector<uint32_t> position) {
    switch (type) {
        case EnemyType::TURTLE:
            return std::make_shared<WalkingEnemy>(gameMap, position, enemyId);
        case EnemyType::YELLOWMON:
            return std::make_shared<FlyingEnemy>(gameMap, position, enemyId);
        case EnemyType::SCHWARZENGUARD:
            return std::make_shared<JumpingEnemy>(gameMap, position, enemyId);
    }
    return nullptr;
}

std::shared_ptr<Item> EntityFactory::createItem(ItemType type, Vector<uint32_t> position) {
    switch (type) {
        case ItemType::FOOD:
            return std::make_shared<Food>(gameMap, position);
        case ItemType::GEM:
            return std::make_shared<Gem>(gameMap, position);
        case ItemType::SILVER_COIN:
            return std::make_shared<SilverCoin>(gameMap, position);
        case ItemType::GOLD_COIN:
            return std::make_shared<GoldCoin>(gameMap, position);
        default:
            return nullptr;
    }
}

std::shared_ptr<Obstacle> EntityFactory::createObstacle(ObstacleType type, Vector<uint32_t> position) {
    switch (type){
        case ObstacleType::FULL_FLOOR:
            return std::make_shared<FullFloor>(gameMap, position);
        case ObstacleType::LEFT_LADDER:
            return std::make_shared<LeftLadder>(gameMap, position);
        case ObstacleType::LONG_PLATFORM:
            return std::make_shared<LongPlatform>(gameMap, position);
        case ObstacleType::RIGHT_LADDER:
            return std::make_shared<RightLadder>(gameMap, position);
        case ObstacleType::SMALL_PLATFORM:
            return std::make_shared<SmallPlatform>(gameMap, position);
        case ObstacleType::COLUMN:   
            return std::make_shared<Column>(gameMap, position);
        default:
            return nullptr;
    }
    return nullptr;
}
