#include "deserializer.h"

#include <iostream>

#include "../../Common/Types/character.h"
#include "../../Common/Types/direction.h"
#include "../../Common/Types/gameMode.h"
#include "../../Common/Types/weapon.h"


Deserializer::Deserializer(std::shared_ptr<Socket> socket): socket(socket) {}


std::unique_ptr<CommandDTO> Deserializer::getCommand(bool& wasClosed, uint32_t& playerId) {
    char cmd = 0;
    socket->recvall(&cmd, 1, &wasClosed);
    std::cout << "Received command: " << (int)cmd << std::endl;
    Command command = static_cast<Command>(cmd);
    switch (command) {
        case Command::CREATE_GAME:
            return deserializeCreateGame(wasClosed, playerId);
        case Command::EPISODES_LIST:
            return deserializeEpisodesList(wasClosed, playerId);
        case Command::JOIN_GAME:
            return deserializeJoinGame(wasClosed, playerId);
        case Command::GAMES_LIST:
            return deserializeGamesList(wasClosed, playerId);
        case Command::START_GAME:
            return deserializeStart(wasClosed, playerId);
        case Command::MOVE:
            return deserializeMove(wasClosed, playerId);
        case Command::SWITCH_WEAPON:
            return deserializeSwitchWeapon(wasClosed, playerId);
        case Command::SPRINT:
            return deserializeSprint(wasClosed, playerId);
        default:
            return nullptr;
    }
}

std::unique_ptr<CreateGameDTO> Deserializer::deserializeCreateGame(bool& wasClosed,
                                                                   uint32_t& playerId) {
    std::string episodeName;
    socket->recvall(&episodeName, sizeof(char), &wasClosed);
    uint8_t maxPlayers;
    socket->recvall(&maxPlayers, sizeof(char), &wasClosed);
    GameMode gameMode = (maxPlayers == 1) ? GameMode::SINGLE_PLAYER : GameMode::PARTY_MODE;
    CharacterType characterType;
    socket->recvall(&characterType, sizeof(char), &wasClosed);
    uint8_t lengthName = 0;
    socket->recvall(&lengthName, sizeof(char), &wasClosed);
    std::vector<char> nameBuffer(lengthName);
    socket->recvall(nameBuffer.data(), lengthName, &wasClosed);
    uint32_t gameId;
    socket->recvall(&gameId, sizeof(uint32_t), &wasClosed);
    return std::make_unique<CreateGameDTO>(playerId, episodeName, maxPlayers, characterType,
                                           std::string(nameBuffer.begin(), nameBuffer.end()),
                                           gameId);
}

std::unique_ptr<EpisodesListDTO> Deserializer::deserializeEpisodesList(bool& wasClosed,
                                                                       uint32_t& playerId) {
    return std::make_unique<EpisodesListDTO>();
}

std::unique_ptr<JoinGameDTO> Deserializer::deserializeJoinGame(bool& wasClosed,
                                                               uint32_t& playerId) {
    uint32_t gameId;
    socket->recvall(&gameId, sizeof(uint32_t), &wasClosed);
    CharacterType characterType;
    socket->recvall(&characterType, sizeof(char), &wasClosed);
    return std::make_unique<JoinGameDTO>(playerId, gameId, characterType);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeGamesList(bool& wasClosed,
                                                               uint32_t& playerId) {
    return std::make_unique<GamesListDTO>();
}


std::unique_ptr<MoveDTO> Deserializer::deserializeMove(bool& wasClosed, uint32_t& playerId) {
    Direction direction;
    socket->recvall(&direction, sizeof(char), &wasClosed);
    return std::make_unique<MoveDTO>(playerId, direction);
}

std::unique_ptr<StartGameDTO> Deserializer::deserializeStart(bool& wasClosed, uint32_t& playerId) {
    uint32_t gameId;
    socket->recvall(&gameId, sizeof(uint32_t), &wasClosed);
    return std::make_unique<StartGameDTO>(playerId, gameId);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeShooting(bool& wasClosed, uint32_t& playerId) {
    return std::make_unique<CommandDTO>(playerId, Command::SHOOT);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeSwitchWeapon(bool& wasClosed,
                                                                  uint32_t& playerId) {
    WeaponType weaponType;
    socket->recvall(&weaponType, sizeof(char), &wasClosed);
    return std::make_unique<SwitchWeaponDTO>(playerId, weaponType);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeSprint(bool& wasClosed, uint32_t& playerId) {
    Direction direction;
    socket->recvall(&direction, sizeof(char), &wasClosed);
    return std::make_unique<MoveDTO>(playerId, direction);
}