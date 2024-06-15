#include <cstring>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../../src/Server/Game/characters/character.h"
#include "../../src/Server/Game/entity.h"
#include "../../src/Server/Game/gameMap.h"

#define MOVEMENTS_PER_CELL 2

TEST(testCharacterMove, testCharacterSpawnsInCorrectPosition) {
    GameMap gameMap({10, 10});
    int16_t playerId = 1;
    Vector<int16_t> characterPos = {5, 5};
    auto character = gameMap.addCharacter(playerId, CharacterType::JAZZ, characterPos);
    Vector<int16_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);

    auto chracaterAtPos = gameMap.getEntityAt(mapPosition);

    ASSERT_EQ(chracaterAtPos, character);
}

TEST(testCharacterMove, testCharacterMoveLeftOneCell) {
    GameMap gameMap({10, 10});
    int16_t playerId = 1;
    Vector<int16_t> characterPos = {5, 5};
    auto character = gameMap.addCharacter(playerId, CharacterType::JAZZ, characterPos);
    Vector<int16_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);

    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        character->moveLeft();
    }

    auto characterAtNewPos = gameMap.getCharacter(playerId);
    auto entityAtOldPos = gameMap.getEntityAt(mapPosition);

    ASSERT_EQ(characterAtNewPos, character);
    ASSERT_EQ(characterAtNewPos->getPosition(), Vector<int16_t>({5 - MOVEMENTS_PER_CELL, 5}));
    ASSERT_EQ(characterAtNewPos->getMapPosition(MOVEMENTS_PER_CELL),
              Vector<int16_t>(
                      {(5 - MOVEMENTS_PER_CELL) / MOVEMENTS_PER_CELL, 5 / MOVEMENTS_PER_CELL}));
    ASSERT_EQ(entityAtOldPos, nullptr);
    ASSERT_EQ(gameMap.isFreePosition(mapPosition), true);
}

TEST(testCharacterMove, testCharacterMoveRightOneCell) {
    GameMap gameMap({10, 10});
    int16_t playerId = 1;
    Vector<int16_t> characterPos = {5, 5};
    auto character = gameMap.addCharacter(playerId, CharacterType::JAZZ, characterPos);

    Vector<int16_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);
    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        character->moveRight();
    }

    auto characterAtNewPos = gameMap.getCharacter(playerId);
    auto entityAtOldPos = gameMap.getEntityAt(mapPosition);

    ASSERT_EQ(characterAtNewPos, character);
    ASSERT_EQ(characterAtNewPos->getPosition(), Vector<int16_t>({5 + MOVEMENTS_PER_CELL, 5}));
    ASSERT_EQ(characterAtNewPos->getMapPosition(MOVEMENTS_PER_CELL),
              Vector<int16_t>(
                      {(5 + MOVEMENTS_PER_CELL) / MOVEMENTS_PER_CELL, 5 / MOVEMENTS_PER_CELL}));
    ASSERT_EQ(entityAtOldPos, nullptr);
    ASSERT_EQ(gameMap.isFreePosition(mapPosition), true);
}

TEST(testCharacterMove, testCharacterAtTheEdgeDoesNotMove) {
    GameMap gameMap({10, 10});
    int16_t playerId = 1;
    Vector<int16_t> characterPos = {0, 5};
    auto character = gameMap.addCharacter(playerId, CharacterType::JAZZ, characterPos);

    Vector<int16_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);
    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        character->moveLeft();
    }

    auto characterAtNewPos = gameMap.getCharacter(playerId);
    auto entityAtOldPos = gameMap.getEntityAt(mapPosition);

    ASSERT_EQ(characterAtNewPos, character);
    ASSERT_EQ(characterAtNewPos->getPosition(), Vector<int16_t>({0, 5}));
    ASSERT_EQ(entityAtOldPos, character);
    ASSERT_EQ(gameMap.isFreePosition(mapPosition), false);
}

TEST(testCharacterMove, testCharacterSpawnsOutOfBounds) {
    GameMap gameMap({10, 10});
    int16_t playerId = 1;
    Vector<int16_t> characterPos = {15, 15};
    auto character = gameMap.addCharacter(playerId, CharacterType::JAZZ, characterPos);

    ASSERT_EQ(character, nullptr);
}


TEST(testCharacterMove, testCharacterMovesOutOfBounds) {
    GameMap gameMap({10, 10});
    int16_t playerId = 1;
    Vector<int16_t> characterPos = {9, 5};
    auto character = gameMap.addCharacter(playerId, CharacterType::JAZZ, characterPos);

    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        character->moveRight();
    }

    auto characterAtNewPos = gameMap.getCharacter(playerId);
    ASSERT_EQ(characterAtNewPos->getPosition(), Vector<int16_t>({9, 5}));
}


TEST(testCharacterMove, testCharacterReceivesDamage) {
    GameMap gameMap({10, 10});
    int16_t playerId = 1;
    Vector<int16_t> characterPos = {5, 5};
    auto character = gameMap.addCharacter(playerId, CharacterType::JAZZ, characterPos);
    int initialHealth = character->getHealth();

    character->recvDamage(10, 1.0f);

    ASSERT_EQ(character->getHealth(), initialHealth - 10);
}


TEST(testCharacterMove, testCharacterHeals) {
    GameMap gameMap({10, 10});
    int16_t playerId = 1;
    Vector<int16_t> characterPos = {5, 5};
    auto character = gameMap.addCharacter(playerId, CharacterType::JAZZ, characterPos);

    character->recvDamage(10, 1.0f);
    int healthAfterDamage = character->getHealth();

    character->heal(5);

    ASSERT_EQ(character->getHealth(), healthAfterDamage + 5);
}


TEST(testCharacterMove, testCharacterIntoxicated) {
    GameMap gameMap({10, 10});
    int16_t playerId = 1;
    Vector<int16_t> characterPos = {5, 5};
    auto character = gameMap.addCharacter(playerId, CharacterType::JAZZ, characterPos);

    character->becomeIntoxicated(5.0f);

    ASSERT_EQ(character->characIsIntoxicated(), true);
    ASSERT_FLOAT_EQ(character->getIntoxicatedTime(), 5.0f);
}


TEST(testCharacterMove, testCharacterDiesAndRevives) {
    GameMap gameMap({10, 10});
    int16_t playerId = 1;
    Vector<int16_t> characterPos = {5, 5};
    auto character = gameMap.addCharacter(playerId, CharacterType::JAZZ, characterPos);
    int initialHealth = character->getHealth();

    character->recvDamage(initialHealth, 1.0f);
    ASSERT_EQ(character->getIsDead(), true);

    character->revive(5.0f);
    ASSERT_EQ(character->getIsDead(), false);
    ASSERT_EQ(character->getHealth(), initialHealth);
}

TEST(testCharacterMove, testCharacterSwitchWeapon) {
    GameMap gameMap({10, 10});
    int16_t playerId = 1;
    Vector<int16_t> characterPos = {5, 5};
    auto character = gameMap.addCharacter(playerId, CharacterType::JAZZ, characterPos);

    character->switchWeapon(WeaponType::BOUNCER);
    // Assuming the Character class has a method to get the current weapon type.
    ASSERT_EQ(character->getCurrentWeaponType(), WeaponType::BOUNCER);
    character->switchWeapon(WeaponType::BLASTER);
    ASSERT_EQ(character->getCurrentWeaponType(), WeaponType::BLASTER);
    character->switchWeapon(WeaponType::FREEZER);
    ASSERT_EQ(character->getCurrentWeaponType(), WeaponType::FREEZER);
    character->switchWeapon(WeaponType::RFMISSILE);
    ASSERT_EQ(character->getCurrentWeaponType(), WeaponType::RFMISSILE);
}

TEST(testCharacterMove, testCharacterCannotMoveWhileIntoxicated) {
    GameMap gameMap({10, 10});
    int16_t playerId = 1;
    Vector<int16_t> characterPos = {5, 5};
    auto character = gameMap.addCharacter(playerId, CharacterType::JAZZ, characterPos);

    character->becomeIntoxicated(5.0f);
    Vector<int16_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);
    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        character->moveRight();
    }

    ASSERT_EQ(character->getPosition(), Vector<int16_t>({5, 5}));
}

TEST(testCharacterMove, testCharacterReceivesContinuousDamage) {
    GameMap gameMap({10, 10});
    int16_t playerId = 1;
    Vector<int16_t> characterPos = {5, 5};
    auto character = gameMap.addCharacter(playerId, CharacterType::JAZZ, characterPos);
    int initialHealth = character->getHealth();

    for (int i = 0; i < 5; i++) {
        character->recvDamage(2, 1.0f);
    }

    ASSERT_EQ(character->getHealth(), initialHealth - 10);
}
