#include "deserializer.h"

#include <iostream>
#include <memory>
#include <vector>

#include <arpa/inet.h>

Deserializer::Deserializer(const std::shared_ptr<Socket>& socket, std::atomic<bool>& keepPlaying, std::atomic<bool>& inGame) :
        socket(socket), keepPlaying(keepPlaying), inGame(inGame), wasClosed(false) {}

std::unique_ptr<CommandDTO> Deserializer::getCommand(uint8_t& playerId) {
    char cmd = 0;
    socket->recvall(&cmd, sizeof(char), &wasClosed);
    std::cout << "[SERVER DESERIALIZER] Received command: " << (int)cmd << std::endl;
    auto command = static_cast<Command>(cmd);
    switch (command) {
        case Command::CREATE_GAME:
            return deserializeCreateGame(playerId);
        case Command::MAPS_LIST:
            return deserializeMapsList(playerId);
        case Command::JOIN_GAME:
            return deserializeJoinGame(playerId);
        case Command::GAMES_LIST:
            return deserializeGamesList(playerId);
        case Command::START_GAME:
            return deserializeStart(playerId);
        case Command::MOVE:
            return deserializeMove(playerId);
        case Command::SWITCH_WEAPON:
            return deserializeSwitchWeapon(playerId);
        case Command::SPRINT:
            return deserializeSprint(playerId);
        default:
            std::cout << "[SERVER DESERIALIZER] Unknown command received: " << (int)cmd
                      << std::endl;
            return nullptr;
    }
}

std::unique_ptr<CreateGameDTO> Deserializer::deserializeCreateGame(uint8_t& playerId) {
    uint8_t mapId;
    socket->recvall(&mapId, sizeof(uint8_t), &wasClosed);
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving mapIdNetwork"
                  << std::endl;
        return nullptr;
    }
    std::cout << "[SERVER DESERIALIZER] Map id: " << (int)mapId << std::endl;

    uint8_t maxPlayers;
    socket->recvall(&maxPlayers, sizeof(uint8_t), &wasClosed);
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
    socket->recvall(&lengthName, sizeof(uint8_t), &wasClosed);
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

bool Deserializer::receive_uint8(uint8_t& value) {
    socket->recvall(&value, sizeof(uint8_t), &wasClosed);
    this->keepPlaying.store(!wasClosed);
    this->inGame.store(!wasClosed);
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving uint8_t"
                  << std::endl;
    }
    return !wasClosed;
}

bool Deserializer::receive_char(char& value) {
    socket->recvall(&value, sizeof(char), &wasClosed);
    this->keepPlaying.store(!wasClosed);
    this->inGame.store(!wasClosed);
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving char"
                  << std::endl;
    }
    return !wasClosed;
}

bool Deserializer::receive_vector_char(std::vector<char>& buffer) {
    socket->recvall(buffer.data(), buffer.size(), &wasClosed);
    this->keepPlaying.store(!wasClosed);
    this->inGame.store(!wasClosed);
    if (wasClosed) {
        std::cerr << "[SERVER DESERIALIZER] Connection was closed while receiving vector<char>"
                  << std::endl;
    }
    return !wasClosed;
}

std::unique_ptr<MapsListDTO> Deserializer::deserializeMapsList(uint8_t& playerId) {
    std::cout << "[SERVER DESERIALIZER] Deserialize Maps List" << std::endl;
    return std::make_unique<MapsListDTO>();
}

std::unique_ptr<JoinGameDTO> Deserializer::deserializeJoinGame(uint8_t& playerId) {
    uint8_t gameId;
    if (!receive_uint8(gameId)) return nullptr;
    char characterTypeChar;
    if (!this->receive_char(characterTypeChar)) return nullptr;
    auto characterType = static_cast<CharacterType>(characterTypeChar);
    return std::make_unique<JoinGameDTO>(playerId, gameId, characterType);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeGamesList(uint8_t& playerId) {
    std::cout << "[SERVER DESERIALIZER] Deserialize Games List" << std::endl;
    return std::make_unique<GamesListDTO>();
}

std::unique_ptr<GameCommandDTO> Deserializer::deserializeMove(uint8_t& playerId) {
    char directionChar;
    if (!this->receive_char(directionChar)) return nullptr;
    auto direction = static_cast<Direction>(directionChar);
    socket->recvall(&direction, sizeof(char), &wasClosed);
    return std::make_unique<GameCommandDTO>(playerId, direction, Command::MOVE);
}

std::unique_ptr<StartGameDTO> Deserializer::deserializeStart(uint8_t& playerId) {
    uint8_t gameId;
    if (!this->receive_uint8(gameId)) return nullptr;
    return std::make_unique<StartGameDTO>(playerId, gameId);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeShooting(uint8_t& playerId) {
    std::cout << "[SERVER DESERIALIZER] Deserialize Shooting" << std::endl;
    return std::make_unique<CommandDTO>(playerId, Command::SHOOT);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeSwitchWeapon(uint8_t& playerId) {
    char weaponTypeChar;
    if (!this->receive_char(weaponTypeChar)) return nullptr;
    auto weaponType = static_cast<WeaponType>(weaponTypeChar);
    return std::make_unique<SwitchWeaponDTO>(playerId, weaponType);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeSprint(uint8_t& playerId) {
    char directionChar;
    if (!this->receive_char(directionChar)) return nullptr;
    auto direction = static_cast<Direction>(directionChar);
    return std::make_unique<GameCommandDTO>(playerId, direction, Command::MOVE);
}
