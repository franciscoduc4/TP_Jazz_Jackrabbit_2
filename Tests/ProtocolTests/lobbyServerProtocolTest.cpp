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

}

TEST(lobbyServerProtocolTest, testSerializeJoinGame) {
    

}


TEST(lobbyServerProtocolTest, testSerializeGamesList) {

}


TEST(lobbyServerProtocolTest, testSerializeStart) {

}
