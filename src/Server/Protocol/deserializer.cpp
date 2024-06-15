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

std::unique_ptr<CommandDTO> Deserializer::getCommand(bool& wasClosed, uint8_t& playerId) {
    char cmd = 0;
    socket->recvall(&cmd, sizeof(char), &wasClosed);
    std::cout << "[SERVER DESERIALIZER] Received command: " << (int)cmd << std::endl;
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
            std::cout << "[SERVER DESERIALIZER] Unknown command received: " << (int)cmd
                      << std::endl;
            return nullptr;
    }
}

std::unique_ptr<CreateGameDTO> Deserializer::deserializeCreateGame(bool& wasClosed,
                                                                   uint8_t& playerId) {
    uint8_t mapIdNetwork;
    socket->recvall(&mapIdNetwork, sizeof(uint8_t), &wasClosed);
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving mapIdNetwork"
                  << std::endl;
        return nullptr;
    }
    std::cout << "[SERVER DESERIALIZER] Map id network: " << mapIdNetwork << std::endl;
    uint8_t mapId = ntohl(mapIdNetwork);

    std::cout << "[SERVER DESERIALIZER] Map id: " << mapId << std::endl;

    uint8_t maxPlayers;
    socket->recvall(&maxPlayers, sizeof(char), &wasClosed);
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving maxPlayers"
                  << std::endl;
        return nullptr;
    }
    std::cout << "[SERVER DESERIALIZER] Max players: " << (int)maxPlayers << std::endl;

    CharacterType characterType;
    socket->recvall(&characterType, sizeof(char), &wasClosed);
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving characterType"
                  << std::endl;
        return nullptr;
    }
    std::cout << "[SERVER DESERIALIZER] Character type: " << (int)characterType << std::endl;

    uint8_t lengthName = 0;
    socket->recvall(&lengthName, sizeof(char), &wasClosed);
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving lengthName"
                  << std::endl;
        return nullptr;
    }
    std::vector<char> nameBuffer(lengthName);
    socket->recvall(nameBuffer.data(), lengthName, &wasClosed);
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving game name"
                  << std::endl;
        return nullptr;
    }
    std::cout << "[SERVER DESERIALIZER] Game name: "
              << std::string(nameBuffer.begin(), nameBuffer.end()) << std::endl;

    return std::make_unique<CreateGameDTO>(playerId, mapId, maxPlayers, characterType,
                                           std::string(nameBuffer.begin(), nameBuffer.end()));
}

std::unique_ptr<MapsListDTO> Deserializer::deserializeMapsList(bool& wasClosed,
                                                               uint8_t& playerId) {
    std::cout << "[SERVER DESERIALIZER] Deserialize Maps List" << std::endl;
    return std::make_unique<MapsListDTO>();
}

std::unique_ptr<JoinGameDTO> Deserializer::deserializeJoinGame(bool& wasClosed, uint8_t& playerId) {
    uint8_t gameId;
    socket->recvall(&gameId, sizeof(uint8_t), &wasClosed);
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving gameId"
                  << std::endl;
        return nullptr;
    }
    CharacterType characterType;
    socket->recvall(&characterType, sizeof(char), &wasClosed);
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving characterType"
                  << std::endl;
        return nullptr;
    }
    return std::make_unique<JoinGameDTO>(playerId, gameId, characterType);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeGamesList(bool& wasClosed, uint8_t& playerId) {
    std::cout << "[SERVER DESERIALIZER] Deserialize Games List" << std::endl;
    return std::make_unique<GamesListDTO>();
}

std::unique_ptr<GameCommandDTO> Deserializer::deserializeMove(bool& wasClosed, uint8_t& playerId) {
    Direction direction;
    socket->recvall(&direction, sizeof(char), &wasClosed);
    std::cout << "[SERVER DESERIALIZER MOVE] Received direction: " << (int)direction << std::endl;
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER MOVE] Connection was closed while receiving direction"
                  << std::endl;
        return nullptr;
    }
    return std::make_unique<GameCommandDTO>(playerId, direction, Command::MOVE);
}

std::unique_ptr<StartGameDTO> Deserializer::deserializeStart(bool& wasClosed, uint8_t& playerId) {
    uint8_t gameId;
    socket->recvall(&gameId, sizeof(uint8_t), &wasClosed);
    gameId = ntohl(gameId);
    std::cout << "[SERVER DESERIALIZER] Game id: " << gameId << std::endl;
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving gameId"
                  << std::endl;
        return nullptr;
    }
    return std::make_unique<StartGameDTO>(playerId, gameId);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeShooting(bool& wasClosed, uint8_t& playerId) {
    std::cout << "[SERVER DESERIALIZER] Deserialize Shooting" << std::endl;
    return std::make_unique<CommandDTO>(playerId, Command::SHOOT);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeSwitchWeapon(bool& wasClosed,
                                                                  uint8_t& playerId) {
    WeaponType weaponType;
    socket->recvall(&weaponType, sizeof(char), &wasClosed);
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving weaponType"
                  << std::endl;
        return nullptr;
    }
    return std::make_unique<SwitchWeaponDTO>(playerId, weaponType);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeSprint(bool& wasClosed, uint8_t& playerId) {
    Direction direction;
    socket->recvall(&direction, sizeof(char), &wasClosed);
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving direction"
                  << std::endl;
        return nullptr;
    }
    return std::make_unique<GameCommandDTO>(playerId, direction, Command::MOVE);
}
