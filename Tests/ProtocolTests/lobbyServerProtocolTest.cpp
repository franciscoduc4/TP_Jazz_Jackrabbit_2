#include <cstdint>
#include <cstring>
#include <memory>

#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../../src//Common/Types/character.h"
#include "../../src/Common/DTO/command.h"
#include "../../src/Common/DTO/createGame.h"
#include "../../src/Common/DTO/gamesList.h"
#include "../../src/Common/DTO/joinGame.h"
#include "../../src/Common/Types/command.h"
#include "../../src/Common/Types/gameMode.h"
#include "../../src/Common/Types/lobbyState.h"
#include "../../src/Common/socket.h"
#include "../../src/Server/Protocol/deserializer.h"
#include "../../src/Server/Protocol/serializer.h"
#include "../../src/Server/Threads/receiver.h"


TEST(lobbyServerProtocolTest, testSerializeCreateGame) {
    Serializer serializer;
    uint8_t gameId = 1;
    auto dto = std::make_unique<CreateGameDTO>(gameId);

    std::vector<char> buffer = serializer.serializeCreateGame(dto);

    ASSERT_EQ(buffer.size(), 1);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::CREATE_GAME));
}

TEST(lobbyServerProtocolTest, testSerializeJoinGame) {
    Serializer serializer;
    uint8_t playerId = 1;
    uint8_t gameId = 1;
    uint8_t currentPlayers = 3;
    auto dto = std::make_unique<JoinGameDTO>(playerId, gameId, currentPlayers);

    std::vector<char> buffer = serializer.serializeJoinGame(dto);

    ASSERT_EQ(buffer.size(), 2);

    uint8_t expectedGameId = gameId;
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&expectedGameId);
    ASSERT_EQ(buffer[0], p[0]);

    uint8_t expectedCurrentPlayers = currentPlayers;
    const unsigned char* p1 = reinterpret_cast<const unsigned char*>(&expectedCurrentPlayers);
    ASSERT_EQ(buffer[1], p1[0]);
}


TEST(lobbyServerProtocolTest, testSerializeGamesList) {
    std::shared_ptr<Socket> skt = std::make_shared<Socket>("8080");
    std::atomic<bool> keepPlaying(true);
    std::atomic<bool> inGame(false);
    Serializer serializer(skt, keepPlaying, inGame);
    std::unordered_map<uint8_t, GameInfo> gamesList;
    gamesList.emplace(0, GameInfo(0, "game1", 4, 2, 0));
    auto dto = std::make_unique<GamesListDTO>(gamesList);

    std::vector<char> buffer = Serializer::serializeGamesList(dto);

    uint8_t expectedSize = gamesList.size();
    const auto* sizePtr = reinterpret_cast<const unsigned char*>(&expectedSize);
    ASSERT_EQ(buffer[0], sizePtr[0]);

    uint8_t expectedGameId1 = 0;
    const auto* p1 = reinterpret_cast<const unsigned char*>(&expectedGameId1);
    ASSERT_EQ(buffer[1], p1[0]);

    uint8_t nameLength1 = 5;
    const auto* nameLenPtr1 = reinterpret_cast<const unsigned char*>(&nameLength1);
    ASSERT_EQ(buffer[2], nameLenPtr1[0]);

    ASSERT_EQ(buffer[3], 'g');
    ASSERT_EQ(buffer[4], 'a');
    ASSERT_EQ(buffer[5], 'm');
    ASSERT_EQ(buffer[6], 'e');
    ASSERT_EQ(buffer[7], '1');

    uint8_t expectedMaxPlayers1 = 4;
    const auto* mp1 = reinterpret_cast<const unsigned char*>(&expectedMaxPlayers1);
    ASSERT_EQ(buffer[8], mp1[0]);

    uint8_t expectedCurrentPlayers1 = 2;
    const auto* cp1 = reinterpret_cast<const unsigned char*>(&expectedCurrentPlayers1);
    ASSERT_EQ(buffer[9], cp1[0]);

    uint8_t expectedMapId1 = 0;
    const auto* mapIdPtr1 = reinterpret_cast<const unsigned char*>(&expectedMapId1);
    ASSERT_EQ(buffer[10], mapIdPtr1[0]);
}


TEST(lobbyServerProtocolTest, testSerializeMapsList) {
    Serializer serializer;
    std::unordered_map<uint8_t, std::string> maps = {{1, "TestMap"}};
    auto dto = std::make_unique<MapsListDTO>(maps);

    std::vector<char> buffer = serializer.serializeMapsList(dto);

    uint8_t expectedSize = 1;
    ASSERT_EQ(buffer[0], expectedSize);
    ASSERT_EQ(buffer[1], 1);
    ASSERT_EQ(buffer[2], maps[1].length());
    ASSERT_EQ(std::string(buffer.begin() + 3, buffer.end()), maps[1]);
}

TEST(lobbyServerProtocolTest, testSerializeGameUpdate) {
    Serializer serializer;
    GameInfo gameInfo(1, "TestGame", 4, 2, 0);
    auto dto = std::make_unique<GameUpdateDTO>(gameInfo);

    std::vector<char> buffer = serializer.serializeGameUpdate(dto);

    ASSERT_EQ(buffer[0], gameInfo.getGameId());
    ASSERT_EQ(buffer[1], gameInfo.name.length());
    ASSERT_EQ(std::string(buffer.begin() + 2, buffer.begin() + 2 + gameInfo.name.length()),
              gameInfo.name);
    ASSERT_EQ(buffer[2 + gameInfo.name.length()], gameInfo.maxPlayers);
    ASSERT_EQ(buffer[3 + gameInfo.name.length()], gameInfo.currentPlayers);
    ASSERT_EQ(buffer[4 + gameInfo.name.length()], gameInfo.mapId);
    ASSERT_EQ(buffer[5 + gameInfo.name.length()], gameInfo.mapName.length());
    ASSERT_EQ(std::string(buffer.begin() + 6 + gameInfo.name.length(), buffer.end()),
              gameInfo.mapName);
}