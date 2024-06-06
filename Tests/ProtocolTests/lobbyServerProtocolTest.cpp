#include <cstdint>
#include <memory>

#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <cstring>

#include "../../src/Common/DTO/command.h"
#include "../../src/Common/DTO/createGame.h"
#include "../../src/Common/DTO/gamesList.h"
#include "../../src/Common/DTO/joinGame.h"
#include "../../src//Common/Types/character.h"
#include "../../src/Common/Types/command.h"
#include "../../src/Common/Types/episode.h"
#include "../../src/Common/Types/gameMode.h"
#include "../../src/Common/Types/lobbyState.h"
#include "../../src/Common/socket.h"
#include "../../src/Server/Protocol/deserializer.h"
#include "../../src/Server/Protocol/serializer.h"
#include "../../src/Server/Threads/receiver.h"



TEST(lobbyServerProtocolTest, testSerializeCreateGame) {
    Serializer serializer;
    int32_t gameId = 1;
    auto dto = std::make_unique<CreateGameDTO>(gameId);

    std::vector<char> buffer = serializer.serializeCreateGame(dto);


    ASSERT_EQ(buffer.size(), 5);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::CREATE_GAME));
    
    int32_t expectedGameId = htonl(gameId);
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&expectedGameId);

    ASSERT_EQ(buffer[1], p[0]);
    ASSERT_EQ(buffer[2], p[1]);
    ASSERT_EQ(buffer[3], p[2]);
    ASSERT_EQ(buffer[4], p[3]);
}

TEST(lobbyServerProtocolTest, testSerializeJoinGame) {
    Serializer serializer;
    int32_t gameId = 1;
    int32_t playerId = 2;
    CharacterType characterType = CharacterType::JAZZ;
    auto dto = std::make_unique<JoinGameDTO>(playerId, gameId, characterType);

    std::vector<char> buffer = serializer.serializeJoinGame(dto);

    ASSERT_EQ(buffer.size(), 5);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::JOIN_GAME));

    int32_t expectedGameId = htonl(gameId);
    const unsigned char* p1 = reinterpret_cast<const unsigned char*>(&expectedGameId);

    ASSERT_EQ(buffer[1], p1[0]);
    ASSERT_EQ(buffer[2], p1[1]);
    ASSERT_EQ(buffer[3], p1[2]);
    ASSERT_EQ(buffer[4], p1[3]);
}



TEST(lobbyServerProtocolTest, testSerializeGamesList) {
    Serializer serializer;
    std::map<int32_t, GameInfo> gamesList;
    gamesList.emplace(1, GameInfo("game1", 4, 2));
    gamesList.emplace(2, GameInfo("game2", 8, 6));
    auto dto = std::make_unique<GamesListDTO>(gamesList);

    std::vector<char> buffer = serializer.serializeGamesList(dto);

    ASSERT_EQ(buffer[0], static_cast<char>(Command::GAMES_LIST));

    // Verificación del primer juego
    int32_t expectedGameId1 = htonl(1);
    const unsigned char* p1 = reinterpret_cast<const unsigned char*>(&expectedGameId1);
    ASSERT_EQ(buffer[1], p1[0]);
    ASSERT_EQ(buffer[2], p1[1]);
    ASSERT_EQ(buffer[3], p1[2]);
    ASSERT_EQ(buffer[4], p1[3]);

    ASSERT_EQ(buffer[5], 5);  // longitud de "game1"
    ASSERT_EQ(buffer[6], 'g');
    ASSERT_EQ(buffer[7], 'a');
    ASSERT_EQ(buffer[8], 'm');
    ASSERT_EQ(buffer[9], 'e');
    ASSERT_EQ(buffer[10], '1');

    int32_t expectedMaxPlayers1 = htonl(4);
    const unsigned char* mp1 = reinterpret_cast<const unsigned char*>(&expectedMaxPlayers1);
    ASSERT_EQ(buffer[11], mp1[0]);
    ASSERT_EQ(buffer[12], mp1[1]);
    ASSERT_EQ(buffer[13], mp1[2]);
    ASSERT_EQ(buffer[14], mp1[3]);

    int32_t expectedCurrentPlayers1 = htonl(2);
    const unsigned char* cp1 = reinterpret_cast<const unsigned char*>(&expectedCurrentPlayers1);
    ASSERT_EQ(buffer[15], cp1[0]);
    ASSERT_EQ(buffer[16], cp1[1]);
    ASSERT_EQ(buffer[17], cp1[2]);
    ASSERT_EQ(buffer[18], cp1[3]);

    // Verificación del segundo juego
    int32_t expectedGameId2 = htonl(2);
    const unsigned char* p2 = reinterpret_cast<const unsigned char*>(&expectedGameId2);
    ASSERT_EQ(buffer[19], p2[0]);
    ASSERT_EQ(buffer[20], p2[1]);
    ASSERT_EQ(buffer[21], p2[2]);
    ASSERT_EQ(buffer[22], p2[3]);

    ASSERT_EQ(buffer[23], 5);  // longitud de "game2"
    ASSERT_EQ(buffer[24], 'g');
    ASSERT_EQ(buffer[25], 'a');
    ASSERT_EQ(buffer[26], 'm');
    ASSERT_EQ(buffer[27], 'e');
    ASSERT_EQ(buffer[28], '2');

    int32_t expectedMaxPlayers2 = htonl(8);
    const unsigned char* mp2 = reinterpret_cast<const unsigned char*>(&expectedMaxPlayers2);
    ASSERT_EQ(buffer[29], mp2[0]);
    ASSERT_EQ(buffer[30], mp2[1]);
    ASSERT_EQ(buffer[31], mp2[2]);
    ASSERT_EQ(buffer[32], mp2[3]);

    int32_t expectedCurrentPlayers2 = htonl(6);
    const unsigned char* cp2 = reinterpret_cast<const unsigned char*>(&expectedCurrentPlayers2);
    ASSERT_EQ(buffer[33], cp2[0]);
    ASSERT_EQ(buffer[34], cp2[1]);
    ASSERT_EQ(buffer[35], cp2[2]);
    ASSERT_EQ(buffer[36], cp2[3]);
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
//     int32_t gameId = htonl(42);  // Asegurarse de que gameId está en network byte order
//     const unsigned char* p = reinterpret_cast<const unsigned char*>(&gameId);
//     inputData.insert(inputData.end(), p, p + sizeof(int32_t));  // Añadir gameId al buffer

//     bool wasClosed = false;
//     int32_t playerId = 1;

//     MockDeserializer deserializer(inputData);
//     std::unique_ptr<CommandDTO> deserializedCommand = deserializer.getCommand(wasClosed, playerId);

//     auto deserializedCreateGameDTO = dynamic_cast<CreateGameDTO*>(deserializedCommand.get());
//     ASSERT_NE(deserializedCreateGameDTO, nullptr);

//     EXPECT_EQ(deserializedCreateGameDTO->getEpisodeName(), Episode::FORMERLY_PRINCE);
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
//     int32_t gameId = htonl(1);
//     const unsigned char* p1 = reinterpret_cast<const unsigned char*>(&gameId);
//     inputData.insert(inputData.end(), p1, p1 + sizeof(int32_t));
//     inputData.push_back(static_cast<char>(CharacterType::JAZZ));

//     bool wasClosed = false;
//     int32_t playerId = 2;

//     MockDeserializer deserializer(inputData);

//     std::unique_ptr<CommandDTO> deserializedCommand = deserializer.getCommand(wasClosed, playerId);

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
//     int32_t playerId = 1;

//     MockDeserializer deserializer(inputData);

//     std::unique_ptr<CommandDTO> deserializedCommand = deserializer.getCommand(wasClosed, playerId);

//     auto deserializedGamesListDTO = dynamic_cast<CommandDTO*>(deserializedCommand.get());
//     ASSERT_NE(deserializedGamesListDTO, nullptr);

//     EXPECT_EQ(deserializedGamesListDTO->getCommand(), Command::GAMES_LIST);
// }

// TEST(lobbyServerProtocolTest, testDeserializeStart) {
//     // Crear datos simulados para el buffer
//     std::vector<char> inputData;
//     inputData.push_back(static_cast<char>(Command::START_GAME));
//     int32_t gameId = htonl(1);
//     const unsigned char* p1 = reinterpret_cast<const unsigned char*>(&gameId);
//     inputData.insert(inputData.end(), p1, p1 + sizeof(int32_t));

//     bool wasClosed = false;
//     int32_t playerId = 1;

//     MockDeserializer deserializer(inputData);

//     std::unique_ptr<CommandDTO> deserializedCommand = deserializer.getCommand(wasClosed, playerId);

//     auto deserializedStartGameDTO = dynamic_cast<StartGameDTO*>(deserializedCommand.get());
//     ASSERT_NE(deserializedStartGameDTO, nullptr);

//     EXPECT_EQ(deserializedStartGameDTO->getGameId(), ntohl(gameId));
// }


