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
    uint32_t gameId = 1;
    auto dto = std::make_unique<CreateGameDTO>(gameId);

    std::vector<char> buffer = serializer.serializeCreateGame(dto);

    ASSERT_EQ(buffer.size(), 5);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::CREATE_GAME));

    uint32_t expectedGameId = htonl(gameId);
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&expectedGameId);

    ASSERT_EQ(buffer[1], p[0]);
    ASSERT_EQ(buffer[2], p[1]);
    ASSERT_EQ(buffer[3], p[2]);
    ASSERT_EQ(buffer[4], p[3]);
}

TEST(lobbyServerProtocolTest, testSerializeJoinGame) {
    Serializer serializer;
    uint32_t gameId = 1;
    uint8_t currentPlayers = 3;
    auto dto = std::make_unique<JoinGameDTO>(gameId, currentPlayers);

    std::vector<char> buffer = serializer.serializeJoinGame(dto);

    ASSERT_EQ(buffer.size(), 6);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::JOIN_GAME));

    uint32_t expectedGameId = htonl(gameId);
    const unsigned char* p2 = reinterpret_cast<const unsigned char*>(&expectedGameId);
    ASSERT_EQ(buffer[1], p2[0]);
    ASSERT_EQ(buffer[2], p2[1]);
    ASSERT_EQ(buffer[3], p2[2]);
    ASSERT_EQ(buffer[4], p2[3]);

    ASSERT_EQ(buffer[5], static_cast<char>(currentPlayers));
}


TEST(lobbyServerProtocolTest, testSerializeGamesList) {
    Serializer serializer;
    std::map<uint32_t, GameInfo> gamesList;
    gamesList.emplace(1, GameInfo("game1", 4, 2));
    gamesList.emplace(2, GameInfo("game2", 8, 6));
    auto dto = std::make_unique<GamesListDTO>(gamesList);

    std::vector<char> buffer = serializer.serializeGamesList(dto);

    ASSERT_EQ(buffer[0], static_cast<char>(Command::GAMES_LIST));

    uint32_t expectedSize = htonl(gamesList.size());
    const unsigned char* sizePtr = reinterpret_cast<const unsigned char*>(&expectedSize);
    ASSERT_EQ(buffer[1], sizePtr[0]);
    ASSERT_EQ(buffer[2], sizePtr[1]);
    ASSERT_EQ(buffer[3], sizePtr[2]);
    ASSERT_EQ(buffer[4], sizePtr[3]);

    uint32_t expectedGameId1 = htonl(1);
    const unsigned char* p1 = reinterpret_cast<const unsigned char*>(&expectedGameId1);
    ASSERT_EQ(buffer[5], p1[0]);
    ASSERT_EQ(buffer[6], p1[1]);
    ASSERT_EQ(buffer[7], p1[2]);
    ASSERT_EQ(buffer[8], p1[3]);

    uint32_t nameLength1 = htonl(5);
    const unsigned char* nameLenPtr1 = reinterpret_cast<const unsigned char*>(&nameLength1);
    ASSERT_EQ(buffer[9], nameLenPtr1[0]);
    ASSERT_EQ(buffer[10], nameLenPtr1[1]);
    ASSERT_EQ(buffer[11], nameLenPtr1[2]);
    ASSERT_EQ(buffer[12], nameLenPtr1[3]);

    ASSERT_EQ(buffer[13], 'g');
    ASSERT_EQ(buffer[14], 'a');
    ASSERT_EQ(buffer[15], 'm');
    ASSERT_EQ(buffer[16], 'e');
    ASSERT_EQ(buffer[17], '1');

    uint32_t expectedMaxPlayers1 = htonl(4);
    const unsigned char* mp1 = reinterpret_cast<const unsigned char*>(&expectedMaxPlayers1);
    ASSERT_EQ(buffer[18], mp1[0]);
    ASSERT_EQ(buffer[19], mp1[1]);
    ASSERT_EQ(buffer[20], mp1[2]);
    ASSERT_EQ(buffer[21], mp1[3]);

    uint32_t expectedCurrentPlayers1 = htonl(2);
    const unsigned char* cp1 = reinterpret_cast<const unsigned char*>(&expectedCurrentPlayers1);
    ASSERT_EQ(buffer[22], cp1[0]);
    ASSERT_EQ(buffer[23], cp1[1]);
    ASSERT_EQ(buffer[24], cp1[2]);
    ASSERT_EQ(buffer[25], cp1[3]);

    // Verificación del segundo juego
    uint32_t expectedGameId2 = htonl(2);
    const unsigned char* p2 = reinterpret_cast<const unsigned char*>(&expectedGameId2);
    ASSERT_EQ(buffer[26], p2[0]);
    ASSERT_EQ(buffer[27], p2[1]);
    ASSERT_EQ(buffer[28], p2[2]);
    ASSERT_EQ(buffer[29], p2[3]);

    uint32_t nameLength2 = htonl(5);
    const unsigned char* nameLenPtr2 = reinterpret_cast<const unsigned char*>(&nameLength2);
    ASSERT_EQ(buffer[30], nameLenPtr2[0]);
    ASSERT_EQ(buffer[31], nameLenPtr2[1]);
    ASSERT_EQ(buffer[32], nameLenPtr2[2]);
    ASSERT_EQ(buffer[33], nameLenPtr2[3]);

    ASSERT_EQ(buffer[34], 'g');
    ASSERT_EQ(buffer[35], 'a');
    ASSERT_EQ(buffer[36], 'm');
    ASSERT_EQ(buffer[37], 'e');
    ASSERT_EQ(buffer[38], '2');

    uint32_t expectedMaxPlayers2 = htonl(8);
    const unsigned char* mp2 = reinterpret_cast<const unsigned char*>(&expectedMaxPlayers2);
    ASSERT_EQ(buffer[39], mp2[0]);
    ASSERT_EQ(buffer[40], mp2[1]);
    ASSERT_EQ(buffer[41], mp2[2]);
    ASSERT_EQ(buffer[42], mp2[3]);

    uint32_t expectedCurrentPlayers2 = htonl(6);
    const unsigned char* cp2 = reinterpret_cast<const unsigned char*>(&expectedCurrentPlayers2);
    ASSERT_EQ(buffer[43], cp2[0]);
    ASSERT_EQ(buffer[44], cp2[1]);
    ASSERT_EQ(buffer[45], cp2[2]);
    ASSERT_EQ(buffer[46], cp2[3]);
}


TEST(lobbyServerProtocolTest, testSerializeStart) {
    Serializer serializer;
    uint32_t playerId = 1;
    uint32_t gameId = 1;
    auto dto = std::make_unique<StartGameDTO>(playerId, gameId);

    std::vector<char> buffer = serializer.serializeStartGame(dto);

    ASSERT_EQ(buffer.size(), 1);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::START_GAME));
}


// class MockDeserializer : public Deserializer {
// public:
//     MockDeserializer(const std::vector<char>& inputData)
//         : Deserializer(nullptr), inputData(inputData), readPos(inputData.cbegin()) {}

// protected:
//     void recvall(void* data, size_t len, bool* wasClosed)  {
//         if (std::distance(readPos, inputData.cend()) < len) {
//             *wasClosed = true;
//             throw std::runtime_error("MockDeserializer: Not enough data to read");
//         }
//         std::memcpy(data, &(*readPos), len);
//         readPos += len;
//         *wasClosed = false;
//     }

// private:
//     std::vector<char> inputData;
//     std::vector<char>::const_iterator readPos;
// };

// TEST(lobbyServerProtocolTest, testDeserializeCreateGame) {
//     // Crear datos simulados para el buffer
//     std::vector<char> inputData;
//     inputData.push_back(static_cast<char>(Command::CREATE_GAME));
//     inputData.push_back(static_cast<char>(Episode::FORMERLY_PRINCE));
//     inputData.push_back(static_cast<char>(GameMode::SINGLE_PLAYER));
//     uint8_t maxPlayers = 4;
//     inputData.push_back(maxPlayers);
//     inputData.push_back(static_cast<char>(CharacterType::JAZZ));
//     uint8_t gameNameLength = 9;
//     inputData.push_back(gameNameLength);
//     std::string gameName = "test_game";
//     inputData.insert(inputData.end(), gameName.begin(), gameName.end());
//     uint32_t gameId = htonl(42);  // Asegurarse de que gameId está en network byte order
//     const unsigned char* p = reinterpret_cast<const unsigned char*>(&gameId);
//     inputData.insert(inputData.end(), p, p + sizeof(uint32_t));  // Añadir gameId al buffer

//     bool wasClosed = false;
//     uint32_t playerId = 1;

//     MockDeserializer deserializer(inputData);
//     std::unique_ptr<CommandDTO> deserializedCommand = deserializer.getCommand(wasClosed,
//     playerId);

//     auto deserializedCreateGameDTO = dynamic_cast<CreateGameDTO*>(deserializedCommand.get());
//     ASSERT_NE(deserializedCreateGameDTO, nullptr);

//     EXPECT_EQ(deserializedCreateGameDTO->getMapName(), Episode::FORMERLY_PRINCE);
//     EXPECT_EQ(deserializedCreateGameDTO->getGameMode(), GameMode::SINGLE_PLAYER);
//     EXPECT_EQ(deserializedCreateGameDTO->getMaxPlayers(), maxPlayers);
//     EXPECT_EQ(deserializedCreateGameDTO->getCharacterType(), CharacterType::JAZZ);
//     EXPECT_EQ(deserializedCreateGameDTO->getGameName(), gameName);
//     EXPECT_EQ(deserializedCreateGameDTO->getGameId(), ntohl(gameId));
// }


// TEST(lobbyServerProtocolTest, testDeserializeJoinGame) {
//     // Crear datos simulados para el buffer
//     std::vector<char> inputData;
//     inputData.push_back(static_cast<char>(Command::JOIN_GAME));
//     uint32_t gameId = htonl(1);
//     const unsigned char* p1 = reinterpret_cast<const unsigned char*>(&gameId);
//     inputData.insert(inputData.end(), p1, p1 + sizeof(uint32_t));
//     inputData.push_back(static_cast<char>(CharacterType::JAZZ));

//     bool wasClosed = false;
//     uint32_t playerId = 2;

//     MockDeserializer deserializer(inputData);

//     std::unique_ptr<CommandDTO> deserializedCommand = deserializer.getCommand(wasClosed,
//     playerId);

//     auto deserializedJoinGameDTO = dynamic_cast<JoinGameDTO*>(deserializedCommand.get());
//     ASSERT_NE(deserializedJoinGameDTO, nullptr);

//     EXPECT_EQ(deserializedJoinGameDTO->getGameId(), ntohl(gameId));
//     EXPECT_EQ(deserializedJoinGameDTO->getCharacterType(), CharacterType::JAZZ);
// }


// TEST(lobbyServerProtocolTest, testDeserializeGamesList) {
//     // Crear datos simulados para el buffer
//     std::vector<char> inputData;
//     inputData.push_back(static_cast<char>(Command::GAMES_LIST));

//     bool wasClosed = false;
//     uint32_t playerId = 1;

//     MockDeserializer deserializer(inputData);

//     std::unique_ptr<CommandDTO> deserializedCommand = deserializer.getCommand(wasClosed,
//     playerId);

//     auto deserializedGamesListDTO = dynamic_cast<CommandDTO*>(deserializedCommand.get());
//     ASSERT_NE(deserializedGamesListDTO, nullptr);

//     EXPECT_EQ(deserializedGamesListDTO->getCommand(), Command::GAMES_LIST);
// }

// TEST(lobbyServerProtocolTest, testDeserializeStart) {
//     // Crear datos simulados para el buffer
//     std::vector<char> inputData;
//     inputData.push_back(static_cast<char>(Command::START_GAME));
//     uint32_t gameId = htonl(1);
//     const unsigned char* p1 = reinterpret_cast<const unsigned char*>(&gameId);
//     inputData.insert(inputData.end(), p1, p1 + sizeof(uint32_t));

//     bool wasClosed = false;
//     uint32_t playerId = 1;

//     MockDeserializer deserializer(inputData);

//     std::unique_ptr<CommandDTO> deserializedCommand = deserializer.getCommand(wasClosed,
//     playerId);

//     auto deserializedStartGameDTO = dynamic_cast<StartGameDTO*>(deserializedCommand.get());
//     ASSERT_NE(deserializedStartGameDTO, nullptr);

//     EXPECT_EQ(deserializedStartGameDTO->getGameId(), ntohl(gameId));
// }
