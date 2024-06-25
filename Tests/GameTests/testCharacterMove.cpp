#include <cstring>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../../src/Server/Game/characters/character.h"
#include "../../src/Server/Game/enemies/enemy.h"
#include "../../src/Server/Game/entity.h"
#include "../../src/Server/Game/gameMap.h"
#include "../../src/Server/Game/items/item.h"
#include "../../src/Server/Game/obstacles/obstacle.h"

#define MOVEMENTS_PER_CELL 2


// TEST(testCharacterMove, testCharacterSpawnsInCorrectPosition) {
//     GameMap gameMap({10, 10}, 0);
//     uint8_t playerId = 0;
//     gameMap.addCharacter(playerId, CharacterType::JAZZ);
//     auto character = gameMap.getCharacter(playerId);
//     Vector<uint32_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);

//     auto chracaterAtPos = gameMap.getEntityAt(mapPosition);

//     ASSERT_EQ(chracaterAtPos, character);
// }

// TEST(testCharacterMove, testCharacterMoveLeftOneCell) {
//     GameMap gameMap({10, 10}, 0);
//     uint8_t playerId = 0;
//     gameMap.addCharacter(playerId, CharacterType::JAZZ);
//     auto character = gameMap.getCharacter(playerId);
//     Vector<uint32_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);

//     for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
//         character->moveLeft();
//     }

//     auto characterAtNewPos = gameMap.getCharacter(playerId);
//     auto entityAtOldPos = gameMap.getEntityAt(mapPosition);

//     ASSERT_EQ(characterAtNewPos, character);
//     ASSERT_EQ(characterAtNewPos->getMapPosition(MOVEMENTS_PER_CELL),
//               Vector<uint8_t>(
//                       {(5 - MOVEMENTS_PER_CELL) / MOVEMENTS_PER_CELL, 5 / MOVEMENTS_PER_CELL}));
//     ASSERT_EQ(entityAtOldPos, nullptr);
//     ASSERT_EQ(gameMap.isFreePosition(mapPosition), true);
// }

// TEST(testCharacterMove, testCharacterMoveRightOneCell) {
//     GameMap gameMap({10, 10}, 0);
//     uint8_t playerId = 0;
//     gameMap.addCharacter(playerId, CharacterType::JAZZ);
//     auto character = gameMap.getCharacter(playerId);
//     Vector<uint32_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);

//     for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
//         character->moveRight();
//     }

//     auto characterAtNewPos = gameMap.getCharacter(playerId);
//     auto entityAtOldPos = gameMap.getEntityAt(mapPosition);

//     ASSERT_EQ(characterAtNewPos, character);
//     ASSERT_EQ(characterAtNewPos->getPosition(), Vector<uint8_t>({5 + MOVEMENTS_PER_CELL, 5}));
//     ASSERT_EQ(characterAtNewPos->getMapPosition(MOVEMENTS_PER_CELL),
//               Vector<uint8_t>(
//                       {(5 + MOVEMENTS_PER_CELL) / MOVEMENTS_PER_CELL, 5 / MOVEMENTS_PER_CELL}));
//     ASSERT_EQ(entityAtOldPos, nullptr);
//     ASSERT_EQ(gameMap.isFreePosition(mapPosition), true);
// }

// TEST(testCharacterMove, testCharacterAtTheEdgeDoesNotMove) {
//     GameMap gameMap({10, 10}, 0);
//     uint8_t playerId = 0;
//     gameMap.addCharacter(playerId, CharacterType::JAZZ);
//     auto character = gameMap.getCharacter(playerId);
//     Vector<uint32_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);

//     for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
//         character->moveLeft();
//     }

//     auto characterAtNewPos = gameMap.getCharacter(playerId);
//     auto entityAtOldPos = gameMap.getEntityAt(mapPosition);

//     ASSERT_EQ(characterAtNewPos, character);
//     ASSERT_EQ(characterAtNewPos->getPosition(), Vector<uint8_t>({0, 5}));
//     ASSERT_EQ(entityAtOldPos, character);
//     ASSERT_EQ(gameMap.isFreePosition(mapPosition), false);
// }

// TEST(testCharacterMove, testCharacterMovesOutOfBounds) {
//     GameMap gameMap({10, 10}, 0);
//     uint8_t playerId = 0;
//     gameMap.addCharacter(playerId, CharacterType::JAZZ);
//     auto character = gameMap.getCharacter(playerId);
//     Vector<uint32_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);

//     for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
//         character->moveRight();
//     }

//     auto characterAtNewPos = gameMap.getCharacter(playerId);
//     ASSERT_EQ(characterAtNewPos->getPosition(), Vector<uint8_t>({9, 5}));
// }


// TEST(testCharacterMove, testCharacterReceivesDamage) {
//     GameMap gameMap({10, 10}, 0);
//     uint8_t playerId = 0;
//     gameMap.addCharacter(playerId, CharacterType::JAZZ);
//     auto character = gameMap.getCharacter(playerId);
//     int initialHealth = character->getHealth();

//     character->recvDamage(10, 1.0f);

//     ASSERT_EQ(character->getHealth(), initialHealth - 10);
// }


// TEST(testCharacterMove, testCharacterHeals) {
//     GameMap gameMap({10, 10}, 0);
//     uint8_t playerId = 0;
//     gameMap.addCharacter(playerId, CharacterType::JAZZ);
//     auto character = gameMap.getCharacter(playerId);

//     character->recvDamage(10, 1.0f);
//     int healthAfterDamage = character->getHealth();

//     character->heal(5);
//     EXPECT_GT(character->getHealth(), healthAfterDamage);
// }


// TEST(testCharacterMove, testCharacterIntoxicated) {
//     GameMap gameMap({10, 10}, 0);
//     uint8_t playerId = 0;
//     gameMap.addCharacter(playerId, CharacterType::JAZZ);
//     auto character = gameMap.getCharacter(playerId);

//     character->becomeIntoxicated(5.0f);
//     EXPECT_TRUE(character->characIsIntoxicated());
//     EXPECT_FLOAT_EQ(character->getIntoxicatedTime(), 5.0f);
// }


// TEST(testCharacterMove, testCharacterDiesAndRevives) {
//     GameMap gameMap({10, 10}, 0);
//     uint8_t playerId = 0;
//     gameMap.addCharacter(playerId, CharacterType::JAZZ);
//     auto character = gameMap.getCharacter(playerId);
//     int initialHealth = character->getHealth();

//     character->recvDamage(initialHealth, 1.0f);
//     ASSERT_EQ(character->getIsDead(), true);

//     character->revive(5.0f);
//     ASSERT_EQ(character->getIsDead(), false);
//     ASSERT_EQ(character->getHealth(), initialHealth);
// }

// TEST(testCharacterMove, testCharacterSwitchWeapon) {
//     GameMap gameMap({10, 10}, 0);
//     uint8_t playerId = 0;
//     gameMap.addCharacter(playerId, CharacterType::JAZZ);
//     auto character = gameMap.getCharacter(playerId);

//     character->switchWeapon(WeaponType::BOUNCER);
//     EXPECT_EQ(character->getCurrentWeaponType(), WeaponType::BOUNCER);
// }


// TEST(testCharacterMove, testCharacterReceivesContinuousDamage) {
//     auto gameMap = std::make_shared<GameMap>(Vector<uint32_t>{1000, 1000}, 0);
//     auto character =
//             std::make_shared<Character>(gameMap, Vector<uint32_t>{100, 100}, 1,
//                                         CharacterType::JAZZ, 1.0f, 2.0f, 1.0f, 10.0f, 0.5f, 30,
//                                         50);
//     uint8_t initialHealth = character->getHealth();
//     character->recvDamage(10);
//     character->recvDamage(10);
//     EXPECT_LT(character->getHealth(), initialHealth);
// }


// TEST(testCharacterMove, testCharacterCannotMoveWhileIntoxicated) {
//     GameMap gameMap({10, 10}, 0);
//     uint8_t playerId = 0;
//     gameMap.addCharacter(playerId, CharacterType::JAZZ);
//     auto character = gameMap.getCharacter(playerId);

//     character->becomeIntoxicated(5.0f);
//     Vector<uint32_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);
//     for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
//         character->moveRight();
//     }

//     ASSERT_EQ(character->getPosition(), Vector<uint8_t>({5, 5}));
// }

// TEST(testCharacterMove, testCharacterReceivesContinuousDamage) {
//     GameMap gameMap({10, 10}, 0);
//     uint8_t playerId = 0;
//     gameMap.addCharacter(playerId, CharacterType::JAZZ);
//     auto character = gameMap.getCharacter(playerId);
//     int initialHealth = character->getHealth();

//     for (int i = 0; i < 5; i++) {
//         character->recvDamage(2, 1.0f);
//     }

//     ASSERT_EQ(character->getHealth(), initialHealth - 10);
// }
