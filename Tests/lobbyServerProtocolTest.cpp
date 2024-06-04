#include <cstdint>
#include <memory>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../Common/DTO/command.h"
#include "../Common/DTO/createGame.h"
#include "../Common/DTO/gamesList.h"
#include "../Common/DTO/joinGame.h"
#include "../Common/Types/character.h"
#include "../Common/Types/command.h"
#include "../Common/Types/episode.h"
#include "../Common/Types/gameMode.h"
#include "../Common/Types/lobbyState.h"
#include "../Common/socket.h"
#include "../Server/Protocol/deserializer.h"
#include "../Server/Protocol/serializer.h"
#include "../Server/Threads/receiver.h"

TEST(lobbyServerProtocolTest, testSerializeCreateGame) {
    Serializer serializer;
    int32_t gameId = 1;
    auto dto = std::make_unique<CreateGameDTO>(gameId);

    std::vector<char> buffer = serializer.serializeCreateGame(dto);

    ASSERT_EQ(buffer.size(), 5);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::CREATE_GAME));
    ASSERT_EQ(buffer[1], 0);
    ASSERT_EQ(buffer[2], 0);
    ASSERT_EQ(buffer[3], 0);
    ASSERT_EQ(buffer[4], static_cast<char>(gameId));
}

TEST(lobbyServerProtocolTest, testSerializeJoinGame) {
    Serializer serializer;
    int32_t gameId = 1;
    int32_t playerId = 2;
    CharacterType characterType = CharacterType::JAZZ;
    auto dto = std::make_unique<JoinGameDTO>(playerId, gameId, characterType);

    std::vector<char> buffer = serializer.serializeJoinGame(dto);

    ASSERT_EQ(buffer.size(), 7);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::JOIN_GAME));
    ASSERT_EQ(buffer[1], 0);
    ASSERT_EQ(buffer[2], 0);
    ASSERT_EQ(buffer[3], 0);
    ASSERT_EQ(buffer[4], static_cast<char>(playerId));
    ASSERT_EQ(buffer[5], static_cast<char>(gameId));
    ASSERT_EQ(buffer[6], static_cast<char>(characterType));
}

TEST(lobbyServerProtocolTest, testSerializeGamesList) {
    Serializer serializer;
    std::map<int32_t, std::string> gamesList;
    gamesList[1] = "game1";
    gamesList[2] = "game2";
    auto dto = std::make_unique<GamesListDTO>(gamesList);

    std::vector<char> buffer = serializer.serializeGamesList(dto);

    ASSERT_EQ(buffer.size(), 13);
    ASSERT_EQ(buffer[0], 1);
    ASSERT_EQ(buffer[1], 5);
    ASSERT_EQ(buffer[2], 'g');
    ASSERT_EQ(buffer[3], 'a');
    ASSERT_EQ(buffer[4], 'm');
    ASSERT_EQ(buffer[5], 'e');
    ASSERT_EQ(buffer[6], 1);
    ASSERT_EQ(buffer[7], 5);
    ASSERT_EQ(buffer[8], 'g');
    ASSERT_EQ(buffer[9], 'a');
    ASSERT_EQ(buffer[10], 'm');
    ASSERT_EQ(buffer[11], 'e');
    ASSERT_EQ(buffer[12], 2);
}

TEST(lobbyServerProtocolTest, testSerializeStart) {
    Serializer serializer;
    int32_t playerId = 1;
    int32_t gameId = 1;
    auto dto = std::make_unique<StartGameDTO>(playerId, gameId);

    std::vector<char> buffer = serializer.serializeStartGame(dto);

    ASSERT_EQ(buffer.size(), 1);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::START_GAME));
}
