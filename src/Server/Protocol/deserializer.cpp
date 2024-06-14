#include "deserializer.h"

#include <iostream>
#include <memory>
#include <vector>

#include <arpa/inet.h>

#include "../../Common/Types/character.h"
#include "../../Common/Types/direction.h"
#include "../../Common/Types/gameMode.h"
#include "../../Common/Types/weapon.h"
#include "../../Common/maps/mapsManager.h"


Deserializer::Deserializer(std::shared_ptr<Socket> socket): socket(socket) {}


std::unique_ptr<CommandDTO> Deserializer::getCommand(bool& wasClosed, uint32_t& playerId) {
    char cmd = 0;
    socket->recvall(&cmd, 1, &wasClosed);
    std::cout << "Received command: " << (int)cmd << std::endl;
    Command command = static_cast<Command>(cmd);
    switch (command) {
        case Command::CREATE_GAME:
            return deserializeCreateGame(wasClosed, playerId);
        case Command::MAPS_LIST:
            return deserializeMapsList(wasClosed, playerId);
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
    // TODO: se envía solamente mapId, el nombre del episodio se obtiene del servidor.
    // std::string mapName;
    // socket->recvall(&mapName, sizeof(char), &wasClosed);
    uint32_t mapIdNetwork;
    socket->recvall(&mapIdNetwork, sizeof(uint32_t), &wasClosed);
    uint32_t mapId = ntohl(mapIdNetwork);
    uint8_t maxPlayers;
    socket->recvall(&maxPlayers, sizeof(char), &wasClosed);
    GameMode gameMode = (maxPlayers == 1) ? GameMode::SINGLE_PLAYER : GameMode::PARTY_MODE;
    CharacterType characterType;
    socket->recvall(&characterType, sizeof(char), &wasClosed);
    uint8_t lengthName = 0;
    socket->recvall(&lengthName, sizeof(char), &wasClosed);
    std::vector<char> nameBuffer(lengthName);
    socket->recvall(nameBuffer.data(), lengthName, &wasClosed);
    // TODO: GameId se tiene que asignar acá.
    // uint32_t gameId;
    // socket->recvall(&gameId, sizeof(uint32_t), &wasClosed);
    std::string mapName = MapsManager::getMapNameById(mapId);
    return std::make_unique<CreateGameDTO>(playerId, mapId, mapName, maxPlayers, characterType,
                                           std::string(nameBuffer.begin(), nameBuffer.end()), -1);
}

std::unique_ptr<MapsListDTO> Deserializer::deserializeMapsList(bool& wasClosed,
                                                                       uint32_t& playerId) {
    return std::make_unique<MapsListDTO>();
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


std::unique_ptr<GameCommandDTO> Deserializer::deserializeMove(bool& wasClosed, uint32_t& playerId) {
    Direction direction;
    socket->recvall(&direction, sizeof(char), &wasClosed);
    return std::make_unique<GameCommandDTO>(playerId, direction, Command::MOVE);
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
    return std::make_unique<GameCommandDTO>(playerId, direction, Command::MOVE);
}
