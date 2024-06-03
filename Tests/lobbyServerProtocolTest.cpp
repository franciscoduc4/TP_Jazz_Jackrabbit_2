#include <gtest/gtest.h>
#include <memory>
#include <arpa/inet.h>
#include "../src/Common/socket.h"
#include "../src/Server/Protocol/deserializer.h"
#include "../src/Server/Protocol/serializer.h"
#include "../src/Common/Types/command.h"
#include "../src/Common/Types/episode.h"
#include "../src/Common/Types/gameMode.h"
#include "../src/Common/Types/character.h"
#include "../src/Common/DTO/createGame.h"
#include "../src/Common/DTO/joinGame.h"
#include "../src/Common/DTO/gamesList.h"
#include "../src/Common/DTO/command.h"
#include "../src/Common/DTO/move.h"
#include "../src/Server/Threads/receiver.h"

// Mock socket class to simulate communication
class MockSocket : public Socket {
public:
    std::vector<char> buffer;

    void sendall(const void* data, size_t len, bool* was_closed)  {
        buffer.insert(buffer.end(), (char*)data, (char*)data + len);
        *was_closed = false;
    }

    void recvall(void* data, size_t len, bool* was_closed)  {
        std::copy(buffer.begin(), buffer.begin() + len, (char*)data);
        buffer.erase(buffer.begin(), buffer.begin() + len);
        *was_closed = false;
    }
};

// Test to check if the server correctly handles a client creating a game
TEST(LobbyProtocolTest, ServerHandlesCreateGame) {
    auto socket = std::make_shared<MockSocket>();
    Deserializer deserializer(socket);

    uint8_t episode = static_cast<uint8_t>(Episode::FORMERLY_PRINCE);
    uint8_t gameMode = static_cast<uint8_t>(GameMode::SINGLE_PLAYER);
    uint8_t maxPlayers = 4;
    uint8_t character = static_cast<uint8_t>(CharacterType::JAZZ);
    uint8_t lengthName = 4;
    std::vector<char> name = {'T', 'e', 's', 't'};
    bool wasClosed = false;

    // Simular recibir el comando
    socket->buffer.push_back(static_cast<char>(Command::CREATE_GAME));
    socket->buffer.push_back(static_cast<char>(episode));
    socket->buffer.push_back(static_cast<char>(gameMode));
    socket->buffer.push_back(static_cast<char>(maxPlayers));
    socket->buffer.push_back(static_cast<char>(character));
    socket->buffer.push_back(static_cast<char>(lengthName));
    socket->buffer.insert(socket->buffer.end(), name.begin(), name.end());

    // Deserializar el comando
    int32_t playerId = 1;
    auto command = deserializer.getCommand(wasClosed, playerId);
    auto createGameDTO = dynamic_cast<CreateGameDTO*>(command.get());
    ASSERT_NE(createGameDTO, nullptr);
    EXPECT_EQ(createGameDTO->getEpisodeName(), Episode::FORMERLY_PRINCE);
    EXPECT_EQ(createGameDTO->getGameMode(), GameMode::SINGLE_PLAYER);
    EXPECT_EQ(createGameDTO->getMaxPlayers(), 4);
    EXPECT_EQ(createGameDTO->getCharacterType(), CharacterType::JAZZ);
    EXPECT_EQ(createGameDTO->getGameName(), "Test");
}

// Test to check if the server correctly handles a client joining a game
TEST(LobbyProtocolTest, ServerHandlesJoinGame) {
    auto socket = std::make_shared<MockSocket>();
    Deserializer deserializer(socket);

    int32_t gameId = 1234;
    uint8_t character = static_cast<uint8_t>(CharacterType::SPAZ);
    bool wasClosed = false;

    // Simular recibir el comando
    socket->buffer.push_back(static_cast<char>(Command::JOIN_GAME));
    int32_t gameIdNetworkOrder = htonl(gameId);
    socket->buffer.insert(socket->buffer.end(), reinterpret_cast<char*>(&gameIdNetworkOrder), 
    reinterpret_cast<char*>(&gameIdNetworkOrder) + sizeof(gameIdNetworkOrder));
    socket->buffer.push_back(static_cast<char>(character));

    // Deserializar el comando
    int32_t playerId = 1;
    auto command = deserializer.getCommand(wasClosed, playerId);
    auto joinGameDTO = dynamic_cast<JoinGameDTO*>(command.get());
    ASSERT_NE(joinGameDTO, nullptr);
    EXPECT_EQ(joinGameDTO->getGameId(), gameId);
    EXPECT_EQ(joinGameDTO->getCharacterType(), CharacterType::SPAZ);
}

// Test to check if the server correctly handles a client requesting the games list
TEST(LobbyProtocolTest, ServerHandlesGamesList) {
    auto socket = std::make_shared<MockSocket>();
    Deserializer deserializer(socket);

    bool wasClosed = false;

    // Simular recibir el comando
    socket->buffer.push_back(static_cast<char>(Command::GAMES_LIST));

    // Deserializar el comando
    int32_t playerId = 1;
    auto command = deserializer.getCommand(wasClosed, playerId);
    auto gamesListDTO = dynamic_cast<CommandDTO*>(command.get());
    ASSERT_NE(gamesListDTO, nullptr);
    EXPECT_EQ(gamesListDTO->getCommand(), Command::GAMES_LIST);
}
