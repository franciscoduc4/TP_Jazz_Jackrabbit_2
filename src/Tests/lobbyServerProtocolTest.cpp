#include <memory>
#include <arpa/inet.h>
#include <gtest/gtest.h>

#include "../Common/DTO/command.h"
#include "../Common/DTO/createGame.h"
#include "../Common/DTO/gamesList.h"
#include "../Common/DTO/joinGame.h"
#include "../Common/DTO/move.h"
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
    CreateGameDTO createGame(gameId);

    std::vector<char> buffer =
            serializer.serializeCreateGame(std::make_unique<CreateGameDTO>(createGame));

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
    JoinGameDTO joinGame(playerId, gameId, characterType);

    std::vector<char> buffer =
            serializer.serializeJoinGame(std::make_unique<JoinGameDTO>(joinGame));

    ASSERT_EQ(buffer.size(), 7);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::JOIN_GAME));
    ASSERT_EQ(buffer[1], 0);
    ASSERT_EQ(buffer[2], 0);
    ASSERT_EQ(buffer[3], 0);
    ASSERT_EQ(buffer[4], static_cast<char>(playerId));
    ASSERT_EQ(buffer[5], static_cast<char>(gameId));
    ASSERT_EQ(buffer[6], static_cast<char>(characterType));
}

// TEST(lobbyServerProtocolTest, testSerializeGamesList) {
//     Serializer serializer;
//     std::map<int32_t, std::string> gamesList;
//     gamesList[1] = "game1";
//     gamesList[2] = "game2";
//     GamesListDTO gamesListDTO(gamesList);

//     std::vector<char> buffer;
//     serializer.serializeGamesList(std::make_unique<GamesListDTO>(gamesList));

//     ASSERT_EQ(buffer.size(), 13);
//     // Aquí tendrías que ajustar la verificación según el contenido exacto de buffer
//     // ASSERT_EQ(buffer[0], 1);
//     // ASSERT_EQ(buffer[1], 5);
//     // ASSERT_EQ(buffer[2], 'g');
//     // ASSERT_EQ(buffer[3], 'a');
//     // ASSERT_EQ(buffer[4], 'm');
//     // ASSERT_EQ(buffer[5], 'e');
//     // ASSERT_EQ(buffer[6], 1);
//     // ASSERT_EQ(buffer[7], 5);
//     // ASSERT_EQ(buffer[8], 'g');
//     // ASSERT_EQ(buffer[9], 'a');
//     // ASSERT_EQ(buffer[10], 'm');
//     // ASSERT_EQ(buffer[11], 'e');
//     // ASSERT_EQ(buffer[12], 2);
// }

// TEST(lobbyServerProtocolTest, testSerializeMove) {
//     Serializer serializer;
//     int32_t playerId = 1;
//     Direction direction = Direction::UP;
//     MoveDTO move(playerId, direction);

//     std::vector<char> buffer = serializer.serializeMove(std::make_unique<MoveDTO>(move));

//     ASSERT_EQ(buffer.size(), 3);
//     ASSERT_EQ(buffer[0], static_cast<char>(Command::MOVE));
//     ASSERT_EQ(buffer[1], static_cast<char>(playerId));
//     ASSERT_EQ(buffer[2], static_cast<char>(direction));
// }

TEST(lobbyServerProtocolTest, testSerializeStart) {
    Serializer serializer;
    CommandDTO command(Command::START_GAME);

    std::vector<char> buffer = serializer.serializeStart(std::make_unique<CommandDTO>(command));

    ASSERT_EQ(buffer.size(), 1);
    ASSERT_EQ(buffer[0], static_cast<char>(Command::START_GAME));
}

// TEST(lobbyServerProtocolTest, testSerializeShooting) {
//     Serializer serializer;
//     CommandDTO command(Command::SHOOT);

//     std::vector<char> buffer = serializer.serializeShooting(std::make_unique<CommandDTO>(command));

//     ASSERT_EQ(buffer.size(), 1);
//     ASSERT_EQ(buffer[0], static_cast<char>(Command::SHOOT));
// }

// TEST(lobbyServerProtocolTest, testSerializeSwitchWeapon) {
//     Serializer serializer;
//     CommandDTO command(Command::SWITCH_WEAPON);

//     std::vector<char> buffer = serializer.serializeSwitchWeapon(std::make_unique<CommandDTO>(command));

//     ASSERT_EQ(buffer.size(), 1);
//     ASSERT_EQ(buffer[0], static_cast<char>(Command::SWITCH_WEAPON));
// }