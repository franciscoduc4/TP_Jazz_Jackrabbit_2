#include "deserializer.h"

#include "../../Common/Types/character.h"
#include "../../Common/Types/episode.h"
#include "../../Common/Types/gameMode.h"
#include "../../Common/Types/move.h"

Deserializer::Deserializer(std::shared_ptr<Socket> socket): socket(socket) {}

std::unique_ptr<CommandDTO> Deserializer::getCommand(bool& wasClosed, int32_t& playerId) {
    char cmd = 0;
    socket->recvall(&cmd, 1, &wasClosed);
    Command command = static_cast<Command>(cmd);
    switch (command) {
        case Command::CREATE_GAME:
            return deserializeCreateGame(wasClosed, playerId);
        case Command::JOIN_GAME:
            return deserializeJoinGame(wasClosed, playerId);
        case Command::GAMES_LIST:
            return deserializeGamesList(wasClosed, playerId);
        case Command::START_GAME:
            return deserializeStart(wasClosed, playerId);
        case Command::MOVE:
            return deserializeMove(wasClosed, playerId);
        default:
            return nullptr;
    }
}

std::unique_ptr<CreateGameDTO> Deserializer::deserializeCreateGame(bool& wasClosed,
                                                                   int32_t& playerId) {
    Episode episodeName;
    socket->recvall(&episodeName, 1, &wasClosed);
    GameMode gameMode;
    socket->recvall(&gameMode, 1, &wasClosed);
    uint8_t maxPlayers;
    socket->recvall(&maxPlayers, 1, &wasClosed);
    CharacterType characterType;
    socket->recvall(&characterType, 1, &wasClosed);
    uint8_t lengthName = 0;
    socket->recvall(&lengthName, 1, &wasClosed);
    std::vector<char> nameBuffer(lengthName);
    socket->recvall(nameBuffer.data(), lengthName, &wasClosed);
    return std::make_unique<CreateGameDTO>(playerId, episodeName, gameMode, maxPlayers,
                                           characterType,
                                           std::string(nameBuffer.begin(), nameBuffer.end()));
}

std::unique_ptr<JoinGameDTO> Deserializer::deserializeJoinGame(bool& wasClosed, int32_t& playerId) {
    int32_t gameId;
    socket->recvall(&gameId, 4, &wasClosed);
    CharacterType characterType;
    socket->recvall(&characterType, 1, &wasClosed);
    return std::make_unique<JoinGameDTO>(playerId, gameId, characterType);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeGamesList(bool& wasClosed, int32_t& playerId) {
    return std::make_unique<CommandDTO>(playerId, Command::GAMES_LIST);
}


std::unique_ptr<MoveDTO> Deserializer::deserializeMove(bool& wasClosed, int32_t& playerId) {
    Move moveType;
    socket->recvall(&moveType, 1, &wasClosed);
    return std::make_unique<MoveDTO>(playerId, moveType);
}

std::unique_ptr<StartGameDTO> Deserializer::deserializeStart(bool& wasClosed, int32_t& playerId) {
    int32_t gameId;
    socket->recvall(&gameId, 4, &wasClosed);
    return std::make_unique<StartGameDTO>(playerId, gameId);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeShooting(bool& wasClosed, int32_t& playerId) {
    return std::make_unique<CommandDTO>(playerId, Command::SHOOT);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeSwitchWeapon(bool& wasClosed,
                                                                  int32_t& playerId) {
    return std::make_unique<CommandDTO>(playerId, Command::SWITCH_WEAPON);
}
