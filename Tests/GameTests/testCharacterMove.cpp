#include <cstring>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../../src/Server/Physics/entity.h"
#include "../../src/Server/Physics/gameMap.h"
#include "../../src/Server/Physics/playerCharacter.h"

#define MOVEMENTS_PER_CELL 2

void testCharacterMoveLeft() {
    GameMap gameMap({10, 10});
    auto character = gameMap.addCharacterAt(CharacterType::JAZZ, {5, 5});

    for (int i = 0; i < MOVEMENTS_PER_CELL; i++) {
        character->move({-1, 0});
    }

    auto chracaterAtNewPos = gameMap.getEntityAt({5 - MOVEMENTS_PER_CELL, 5});
    auto chracaterAtOldPos = gameMap.getEntityAt({5, 5});

    ASSERT_EQ(chracaterAtNewPos, character);
    ASSERT_EQ(chracaterAtOldPos, nullptr);
}