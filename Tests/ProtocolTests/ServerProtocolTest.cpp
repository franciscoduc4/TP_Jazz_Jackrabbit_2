#include <atomic>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/Server/Protocol/deserializer.h"
#include "../../src/Server/Protocol/serializer.h"

#include "socket.h"

class MockSocket : public Socket {
public:
    explicit MockSocket(const std::string& port) : Socket(port.c_str()) {}
    MOCK_METHOD(int, sendall, (const void* msg, unsigned int len, bool* wasClosed), (override));
    MOCK_METHOD(int, recvall, (void* msg, unsigned int len, bool* wasClosed), (override));
};

class SerializerTest : public ::testing::Test {
protected:
    std::shared_ptr<MockSocket> mockSocket;
    std::atomic<bool> keepPlaying;
    std::atomic<bool> inGame;
    Serializer serializer;

    SerializerTest() :
            mockSocket(std::make_shared<MockSocket>("8080")),
            keepPlaying(true),
            inGame(true),
            serializer(mockSocket, keepPlaying, inGame) {}
};

TEST_F(SerializerTest, SendIdSendsCorrectId) {
    uint8_t playerId = 5;
    EXPECT_CALL(*mockSocket, sendall(::testing::_, ::testing::_, ::testing::_))
            .WillOnce([playerId](const void* msg, size_t len, bool* wasClosed) {
                EXPECT_EQ(len, sizeof(uint8_t));
                EXPECT_EQ(*static_cast<const uint8_t*>(msg), playerId);
                return len;
            });

    serializer.sendId(playerId);
}


TEST_F(SerializerTest, SendCommandSendsCorrectCommand) {
    std::unique_ptr<CommandDTO> commandDto = std::make_unique<CreateGameDTO>(0, 1, CharacterType::JAZZ, "Null");
    EXPECT_CALL(*mockSocket, sendall(::testing::_, ::testing::_, ::testing::_))
            .Times(3)
            .WillOnce([&commandDto](const void* msg, size_t len, bool* wasClosed) {
                EXPECT_EQ(len, sizeof(char));
                EXPECT_EQ(*static_cast<const char*>(msg), static_cast<char>(commandDto->getType()));
                return len;
            })
            .WillOnce([&commandDto](const void* msg, size_t len, bool* wasClosed) {
                EXPECT_EQ(len, sizeof(char));
                EXPECT_EQ(*static_cast<const char*>(msg), static_cast<char>(commandDto->getCommand()));
                return len;
            })
            .WillOnce([&commandDto](const void* msg, size_t len, bool* wasClosed) {
                EXPECT_EQ(len, sizeof(uint8_t));
                EXPECT_EQ(*static_cast<const uint8_t*>(msg), commandDto->getPlayerId());
                return len;
            });

    serializer.sendCommand(commandDto);
}

TEST_F(SerializerTest, SendGameDTOSendsCorrectData) {
    std::vector<PlayerDTO> players = {PlayerDTO(0, 0, 0, 100, 50, 40, CharacterType::JAZZ, CharacterStateEntity::IDLE, 0)};
    std::vector<EnemyDTO> enemies = {EnemyDTO(1, 10, 100, 5, 50, 50, EnemyType::SCHWARZENGUARD, EnemyStateEntity::ENEMY_IDLE)};
    std::vector<BulletDTO> bullets = {BulletDTO(1, 10, 5, 50, 50, 1)};
    std::vector<ItemDTO> items = {ItemDTO(50, 50, ItemType::GEM)};
    std::vector<WeaponDTO> weapons = {WeaponDTO(1, 10, 5, 3, 50)};
    std::vector<TileDTO> tiles = {TileDTO(50, 50, ObstacleType::COLUMN)};
    auto gameDto = std::make_unique<GameDTO>(players, enemies, bullets, items, weapons, tiles);

    EXPECT_CALL(*mockSocket, sendall(::testing::_, ::testing::_, ::testing::_))
            .Times(::testing::AtLeast(1));

    serializer.sendGameDTO(gameDto);
}


class DeserializerTest : public ::testing::Test {
protected:
    std::shared_ptr<MockSocket> mockSocket;
    std::atomic<bool> keepPlaying;
    std::atomic<bool> inGame;
    Deserializer deserializer;

    DeserializerTest() :
            mockSocket(std::make_shared<MockSocket>("8080")),
            keepPlaying(true),
            inGame(true),
            deserializer(mockSocket, keepPlaying, inGame){}
};

TEST_F(DeserializerTest, DeserializeCreateGameReturnsCorrectDTO) {
    uint8_t playerId = 1;
    uint8_t mapId = 2;
    uint8_t maxPlayers = 3;
    CharacterType characterType = CharacterType::JAZZ;
    std::string gameName = "TestGame";
    std::vector<char> nameBuffer(gameName.begin(), gameName.end());

    EXPECT_CALL(*mockSocket, recvall(testing::_, testing::_, testing::_))
            .Times(6)
            .WillOnce(testing::Invoke([&](void* buffer, size_t len, bool* wasClosed) {
                *(static_cast<char*>(buffer)) = static_cast<char>(Command::CREATE_GAME);
                return len;
            }))
            .WillOnce(testing::Invoke([&](void* buffer, size_t len, bool* wasClosed) {
                *(static_cast<uint8_t*>(buffer)) = mapId;
                return len;
            }))
            .WillOnce(testing::Invoke([&](void* buffer, size_t len, bool* wasClosed) {
                *(static_cast<uint8_t*>(buffer)) = maxPlayers;
                return len;
            }))
            .WillOnce(testing::Invoke([&](void* buffer, size_t len, bool* wasClosed) {
                *(static_cast<CharacterType*>(buffer)) = characterType;
                return len;
            }))
            .WillOnce(testing::Invoke([&](void* buffer, size_t len, bool* wasClosed) {
                *(static_cast<uint8_t*>(buffer)) = gameName.size();
                return len;
            }))
            .WillOnce(testing::Invoke([&](void* buffer, size_t len, bool* wasClosed) {
                std::copy(nameBuffer.begin(), nameBuffer.end(), static_cast<char*>(buffer));
                return len;
            }));

    auto dto = deserializer.getCommand(playerId);

    ASSERT_NE(dto, nullptr);

    auto createGameDto = dynamic_cast<CreateGameDTO*>(dto.get());

    EXPECT_EQ(createGameDto->getPlayerId(), playerId);
    EXPECT_EQ(createGameDto->getMapId(), mapId);
    EXPECT_EQ(createGameDto->getMaxPlayers(), maxPlayers);
    EXPECT_EQ(createGameDto->getCharacterType(), characterType);
    EXPECT_EQ(createGameDto->getGameName(), gameName);
}

TEST_F(DeserializerTest, DeserializeCreateGameReturnsNullOnSocketClose) {
    uint8_t playerId = 1;

    EXPECT_CALL(*mockSocket, recvall(testing::_, testing::_, testing::_))
            .WillOnce(testing::Invoke([](void* buffer, size_t len, bool* wasClosed) {
                *wasClosed = true;
                return 0;
            }));

    auto dto = deserializer.getCommand(playerId);

    EXPECT_EQ(dto, nullptr);
}