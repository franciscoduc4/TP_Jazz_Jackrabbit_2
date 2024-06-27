#include "deserializer.h"

#include <iostream>
#include <memory>
#include <vector>

#include <arpa/inet.h>

#include "protocol.h"

Deserializer::Deserializer(const std::shared_ptr<Socket>& socket, std::atomic<bool>& keepPlaying,
                           std::atomic<bool>& inGame):
        protocol(std::make_shared<Protocol>(socket, keepPlaying, inGame)) {}

std::unique_ptr<CommandDTO> Deserializer::getCommand(uint8_t& playerId) {
    char cmd = 0;
    if (!protocol->receiveChar(cmd)) {
        return nullptr;
    }

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
        case Command::IDLE:
            return deserializeIdle(playerId);
        case Command::MOVE:
            return deserializeMove(playerId);
        case Command::SWITCH_WEAPON:
            return deserializeSwitchWeapon(playerId);
        case Command::SHOOT:
            return deserializeShooting(playerId);
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
    protocol->receiveUInt8(mapId);
    std::cout << "[SERVER DESERIALIZER] Map id: " << (int)mapId << std::endl;

    uint8_t maxPlayers;
    protocol->receiveUInt8(maxPlayers);
    std::cout << "[SERVER DESERIALIZER] Max players: " << (int)maxPlayers << std::endl;

    char characterTypeChar;
    protocol->receiveChar(characterTypeChar);
    auto characterType = static_cast<CharacterType>(characterTypeChar);
    std::cout << "[SERVER DESERIALIZER] Character type: " << (int)characterType << std::endl;

    uint8_t lengthName;
    protocol->receiveUInt8(lengthName);
    std::vector<char> nameBuffer(lengthName);
    protocol->receiveVectorChar(nameBuffer);
    std::string gameName(nameBuffer.begin(), nameBuffer.end());
    std::cout << "[SERVER DESERIALIZER] Game name: " << gameName << std::endl;

    return std::make_unique<CreateGameDTO>(playerId, mapId, maxPlayers, characterType, gameName);
}

std::unique_ptr<JoinGameDTO> Deserializer::deserializeJoinGame(uint8_t& playerId) {
    uint8_t gameId;
    if (!protocol->receiveUInt8(gameId))
        return nullptr;
    char characterTypeChar;
    if (!protocol->receiveChar(characterTypeChar))
        return nullptr;
    auto characterType = static_cast<CharacterType>(characterTypeChar);
    return std::make_unique<JoinGameDTO>(playerId, gameId, characterType);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeGamesList(uint8_t& playerId) {
    std::cout << "[SERVER DESERIALIZER] Deserialize Games List" << std::endl;
    return std::make_unique<GamesListDTO>();
}

std::unique_ptr<CommandDTO> Deserializer::deserializeIdle(uint8_t& playerId) {
    std::cout << "[SERVER DESERIALIZER] Deserialize Idle" << std::endl;
    return std::make_unique<GameCommandDTO>(playerId, Direction::UP, Command::IDLE);
}

std::unique_ptr<GameCommandDTO> Deserializer::deserializeMove(uint8_t& playerId) {
    char directionChar;
    if (!protocol->receiveChar(directionChar))
        return nullptr;
    Direction direction = static_cast<Direction>(directionChar);
    return std::make_unique<GameCommandDTO>(playerId, direction, Command::MOVE);
}

std::unique_ptr<StartGameDTO> Deserializer::deserializeStart(uint8_t& playerId) {
    uint8_t gameId;
    if (!protocol->receiveUInt8(gameId))
        return nullptr;
    return std::make_unique<StartGameDTO>(playerId, gameId);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeShooting(uint8_t& playerId) {
    std::cout << "[SERVER DESERIALIZER] Deserialize Shooting" << std::endl;
    return std::make_unique<CommandDTO>(playerId, Command::SHOOT);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeSwitchWeapon(uint8_t& playerId) {
    char weaponTypeChar;
    if (!protocol->receiveChar(weaponTypeChar))
        return nullptr;
    auto weaponType = static_cast<WeaponType>(weaponTypeChar);
    std::cout << "[SERVER DESERIALIZER] Deserialized SwitchWeapon command with WeaponType: "
              << (int)weaponType << std::endl;
    return std::make_unique<SwitchWeaponDTO>(playerId, weaponType);
}

std::unique_ptr<CommandDTO> Deserializer::deserializeSprint(uint8_t& playerId) {
    return std::make_unique<GameCommandDTO>(playerId, Command::SPRINT);
}

std::unique_ptr<MapsListDTO> Deserializer::deserializeMapsList(uint8_t& playerId) {
    std::cout << "[SERVER DESERIALIZER] Deserialize Maps List" << std::endl;
    return std::make_unique<MapsListDTO>();
}
