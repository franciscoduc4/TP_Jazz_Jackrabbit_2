#include <cstring>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../../src/Server/Game/characters/character.h"
#include "../../src/Server/Game/entity.h"
#include "../../src/Server/Game/gameMap.h"

#define MOVEMENTS_PER_CELL 2

TEST(testCharacterMove, testCharacterSpawnsInCorrectPosition) {
    GameMap gameMap({10, 10});
    int16_t characterId = 1;
    Vector<int16_t> characterPos = {5, 5};
    auto character = gameMap.addCharacter(characterId, CharacterType::JAZZ, characterPos);
    Vector<int16_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);

    auto chracaterAtPos = gameMap.getEntityAt(mapPosition);

    ASSERT_EQ(chracaterAtPos, character);
}

TEST(testCharacterMove, testCharacterMoveLeftOneCell) {
    GameMap gameMap({10, 10});
    int16_t characterId = 1;
    Vector<int16_t> characterPos = {5, 5};
    auto character = gameMap.addCharacter(characterId, CharacterType::JAZZ, characterPos);
    Vector<int16_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);

    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        character->moveLeft();
    }

    auto characterAtNewPos = gameMap.getCharacter(characterId);
    auto entityAtOldPos = gameMap.getEntityAt(mapPosition);

    ASSERT_EQ(characterAtNewPos, character);
    ASSERT_EQ(characterAtNewPos->getPosition(), Vector<int16_t>({5 - MOVEMENTS_PER_CELL, 5}));
    ASSERT_EQ(entityAtOldPos, nullptr);
    ASSERT_EQ(gameMap.isFreePosition(mapPosition), true);
}

TEST(testCharacterMove, testCharacterMoveRightOneCell) {
    GameMap gameMap({10, 10});
    int16_t characterId = 1;
    Vector<int16_t> characterPos = {5, 5};
    auto character = gameMap.addCharacter(characterId, CharacterType::JAZZ, characterPos);
    Vector<int16_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);
    std::cout << "x: " << mapPosition.x << " y: " << mapPosition.y << std::endl;
    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        character->moveRight();
    }

    auto characterAtNewPos = gameMap.getCharacter(characterId);
    auto entityAtOldPos = gameMap.getEntityAt(mapPosition);

    std::cout << "x: " << entityAtOldPos->getMapPosition(MOVEMENTS_PER_CELL).x
              << " y: " << entityAtOldPos->getMapPosition(MOVEMENTS_PER_CELL).y << std::endl;

    ASSERT_EQ(characterAtNewPos, character);
    ASSERT_EQ(characterAtNewPos->getPosition(), Vector<int16_t>({5 + MOVEMENTS_PER_CELL, 5}));
    ASSERT_EQ(entityAtOldPos, nullptr);
    ASSERT_EQ(gameMap.isFreePosition(mapPosition), true);
}

TEST(testCharacterMove, testCharacterAtTheEdgeDoesNotMove) {
    GameMap gameMap({10, 10});
    int16_t characterId = 1;
    Vector<int16_t> characterPos = {0, 5};
    auto character = gameMap.addCharacter(characterId, CharacterType::JAZZ, characterPos);
    Vector<int16_t> mapPosition = character->getMapPosition(MOVEMENTS_PER_CELL);

    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        character->moveLeft();
    }

    auto characterAtNewPos = gameMap.getCharacter(characterId);
    auto entityAtOldPos = gameMap.getEntityAt(mapPosition);

    ASSERT_EQ(characterAtNewPos, character);
    ASSERT_EQ(characterAtNewPos->getPosition(), Vector<int16_t>({0, 5}));
    ASSERT_EQ(entityAtOldPos, character);
    ASSERT_EQ(gameMap.isFreePosition(mapPosition), false);
}
