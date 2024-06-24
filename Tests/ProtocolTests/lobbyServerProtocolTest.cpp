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
    std::shared_ptr<Socket> skt = std::make_shared<Socket>("8080");
    std::atomic<bool> keepPlaying(true);
    std::atomic<bool> inGame(false);
    Serializer serializer(skt, keepPlaying, inGame);
    uint8_t gameId = 1;
    std::unique_ptr<CreateGameDTO> dto = std::make_unique<CreateGameDTO>(gameId);

    std::vector<char> buffer = Serializer::serializeCreateGame(dto);

    ASSERT_EQ(buffer.size(), 1);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::CREATE_GAME));

    uint8_t expectedGameId = gameId;
    const auto* p = reinterpret_cast<const unsigned char*>(&expectedGameId);

    ASSERT_EQ(buffer[0], p[0]);
}

TEST(lobbyServerProtocolTest, testSerializeJoinGame) {
    std::shared_ptr<Socket> skt = std::make_shared<Socket>("8080");
    std::atomic<bool> keepPlaying(true);
    std::atomic<bool> inGame(false);
    Serializer serializer(skt, keepPlaying, inGame);
    uint8_t gameId = 1;
    uint8_t currentPlayers = 3;
    auto dto = std::make_unique<JoinGameDTO>(gameId, currentPlayers);

    std::vector<char> buffer = Serializer::serializeJoinGame(dto);

    ASSERT_EQ(buffer.size(), 2);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::JOIN_GAME));

    uint32_t expectedGameId = htonl(gameId);
    const auto* p2 = reinterpret_cast<const unsigned char*>(&expectedGameId);
    ASSERT_EQ(buffer[1], p2[0]);
    ASSERT_EQ(buffer[2], p2[1]);
    ASSERT_EQ(buffer[3], p2[2]);
    ASSERT_EQ(buffer[4], p2[3]);

    ASSERT_EQ(buffer[5], static_cast<char>(currentPlayers));
}


TEST(lobbyServerProtocolTest, testSerializeGamesList) {
    std::shared_ptr<Socket> skt = std::make_shared<Socket>("8080");
    std::atomic<bool> keepPlaying(true);
    std::atomic<bool> inGame(false);
    Serializer serializer(skt, keepPlaying, inGame);
    std::unordered_map<uint8_t, GameInfo> gamesList;
    gamesList.emplace(0, GameInfo(0, "game1", 4, 2));
    gamesList.emplace(1, GameInfo(1, "game2", 8, 6));
    auto dto = std::make_unique<GamesListDTO>(gamesList);

    std::vector<char> buffer = Serializer::serializeGamesList(dto);

    ASSERT_EQ(buffer[0], static_cast<char>(Command::GAMES_LIST));

    uint8_t expectedSize = gamesList.size();
    const auto* sizePtr = reinterpret_cast<const unsigned char*>(&expectedSize);
    ASSERT_EQ(buffer[1], sizePtr[0]);

    uint8_t expectedGameId1 = 1;
    const auto* p1 = reinterpret_cast<const unsigned char*>(&expectedGameId1);
    ASSERT_EQ(buffer[2], p1[0]);

    uint8_t nameLength1 = 5;
    const auto* nameLenPtr1 = reinterpret_cast<const unsigned char*>(&nameLength1);
    ASSERT_EQ(buffer[3], nameLenPtr1[0]);

    ASSERT_EQ(buffer[4], 'g');
    ASSERT_EQ(buffer[5], 'a');
    ASSERT_EQ(buffer[6], 'm');
    ASSERT_EQ(buffer[7], 'e');
    ASSERT_EQ(buffer[8], '1');

    uint8_t expectedMaxPlayers1 = 4;
    const auto* mp1 = reinterpret_cast<const unsigned char*>(&expectedMaxPlayers1);
    ASSERT_EQ(buffer[9], mp1[0]);

    uint8_t expectedCurrentPlayers1 = 2;
    const auto* cp1 = reinterpret_cast<const unsigned char*>(&expectedCurrentPlayers1);
    ASSERT_EQ(buffer[10], cp1[0]);

    // Verificación del segundo juego
    uint8_t expectedGameId2 = 2;
    const auto* p2 = reinterpret_cast<const unsigned char*>(&expectedGameId2);
    ASSERT_EQ(buffer[11], p2[0]);

    uint8_t nameLength2 = 5;
    const auto* nameLenPtr2 = reinterpret_cast<const unsigned char*>(&nameLength2);
    ASSERT_EQ(buffer[12], nameLenPtr2[0]);

    ASSERT_EQ(buffer[13], 'g');
    ASSERT_EQ(buffer[14], 'a');
    ASSERT_EQ(buffer[15], 'm');
    ASSERT_EQ(buffer[16], 'e');
    ASSERT_EQ(buffer[17], '2');

    uint8_t expectedMaxPlayers2 = 8;
    const auto* mp2 = reinterpret_cast<const unsigned char*>(&expectedMaxPlayers2);
    ASSERT_EQ(buffer[18], mp2[0]);

    uint8_t expectedCurrentPlayers2 = 6;
    const auto* cp2 = reinterpret_cast<const unsigned char*>(&expectedCurrentPlayers2);
    ASSERT_EQ(buffer[19], cp2[0]);
}


/*TEST(lobbyServerProtocolTest, testSerializeStart) {
    std::shared_ptr<Socket> skt = std::make_shared<Socket>("8080");
    std::atomic<bool> keepPlaying(true);
    std::atomic<bool> inGame(false);
    Serializer serializer(skt, keepPlaying, inGame);
    uint32_t playerId = 1;
    uint8_t gameId = 1;
    auto dto = std::make_unique<StartGameDTO>(playerId, gameId);

    std::vector<char> buffer = Serializer::serializeStartGame(dto);

    ASSERT_EQ(buffer.size(), 1);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::START_GAME));
}*/
