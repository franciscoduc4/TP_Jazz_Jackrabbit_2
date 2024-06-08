#include "serializer.h"

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include <arpa/inet.h>

Serializer::Serializer(std::shared_ptr<Socket> socket): socket(socket) {}

void Serializer::sendCommand(const std::unique_ptr<CommandDTO> dto, bool& wasClosed) {
    std::cout << "Sending command" << std::endl;
    Command command = dto->getCommand();
    socket->sendall(&command, 1, &wasClosed);
    std::vector<char> buffer;

    switch (command) {
        case Command::CREATE_GAME:
            buffer = serializeCreateGame(
                    std::make_unique<CreateGameDTO>(static_cast<const CreateGameDTO&>(*dto)));
            break;
        case Command::JOIN_GAME:
            buffer = serializeJoinGame(
                    std::make_unique<JoinGameDTO>(static_cast<const JoinGameDTO&>(*dto)));
            break;
        case Command::GAMES_LIST:
            buffer = serializeGamesList(
                    std::make_unique<GamesListDTO>(static_cast<const GamesListDTO&>(*dto)));
            break;
        case Command::START_GAME:
            buffer = serializeStartGame(
                    std::make_unique<StartGameDTO>(static_cast<const StartGameDTO&>(*dto)));
            break;
        default:
            return;
    }
    socket->sendall(buffer.data(), buffer.size(), &wasClosed);
}

std::vector<char> Serializer::serializeGameDTO(const std::unique_ptr<GameDTO> dto) {
    std::vector<char> buffer;
    std::vector<PlayerDTO> players = dto->getPlayers();
    for (const auto& player: players) {
        std::vector<char> playerBuffer = serializePlayerDTO(std::make_unique<PlayerDTO>(player));
        buffer.insert(buffer.end(), playerBuffer.begin(), playerBuffer.end());
    }

    std::vector<EnemyDTO> enemies = dto->getEnemies();
    for (const auto& enemy: enemies) {
        std::vector<char> enemyBuffer = serializeEnemyDTO(std::make_unique<EnemyDTO>(enemy));
        buffer.insert(buffer.end(), enemyBuffer.begin(), enemyBuffer.end());
    }

    std::vector<BulletDTO> bullets = dto->getBullets();
    for (const auto& bullet: bullets) {
        std::vector<char> bulletBuffer = serializeBulletDTO(std::make_unique<BulletDTO>(bullet));
        buffer.insert(buffer.end(), bulletBuffer.begin(), bulletBuffer.end());
    }

    std::vector<ItemDTO> items = dto->getItems();
    for (const auto& item: items) {
        std::vector<char> itemBuffer = serializeItemDTO(std::make_unique<ItemDTO>(item));
        buffer.insert(buffer.end(), itemBuffer.begin(), itemBuffer.end());
    }

    std::vector<WeaponDTO> weapons = dto->getWeapons();
    for (const auto& weapon: weapons) {
        std::vector<char> weaponBuffer = serializeWeaponDTO(std::make_unique<WeaponDTO>(weapon));
        buffer.insert(buffer.end(), weaponBuffer.begin(), weaponBuffer.end());
    }

    std::vector<TileDTO> tiles = dto->getTiles();
    for (const auto& tile: tiles) {
        std::vector<char> tileBuffer = serializeTileDTO(std::make_unique<TileDTO>(tile));
        buffer.insert(buffer.end(), tileBuffer.begin(), tileBuffer.end());
    }

    return buffer;
}

std::vector<char> Serializer::serializeCreateGame(const std::unique_ptr<CreateGameDTO>& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::CREATE_GAME));
    int32_t gameId = htonl(dto->getGameId());
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&gameId);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    return buffer;
}

std::vector<char> Serializer::serializeJoinGame(const std::unique_ptr<JoinGameDTO>& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::JOIN_GAME));
    int32_t playerId = htonl(dto->getPlayerId());
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&playerId);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    int32_t gameId = htonl(dto->getGameId());
    const unsigned char* p1 = reinterpret_cast<const unsigned char*>(&gameId);
    buffer.insert(buffer.end(), p1, p1 + sizeof(int32_t));
    uint8_t currentPlayers = dto->getCurrentPlayers();
    buffer.push_back(static_cast<char>(currentPlayers));

    return buffer;
}


std::vector<char> Serializer::serializeGamesList(const std::unique_ptr<GamesListDTO>& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::GAMES_LIST));
    auto games = dto->getGames();
    int32_t gamesSize = htonl(games.size());
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&gamesSize);
    buffer.insert(buffer.end(), p, p + sizeof(int32_t));
    for (const auto& [id, gameInfo]: games) {
        int32_t gameId = htonl(id);
        const unsigned char* p = reinterpret_cast<const unsigned char*>(&gameId);
        buffer.insert(buffer.end(), p, p + sizeof(int32_t));

        int32_t nameLength = htonl(gameInfo.name.length());
        const unsigned char* np = reinterpret_cast<const unsigned char*>(&nameLength);
        buffer.insert(buffer.end(), np, np + sizeof(int32_t));

        buffer.insert(buffer.end(), gameInfo.name.begin(), gameInfo.name.end());

        int32_t maxPlayers = htonl(gameInfo.maxPlayers);
        const unsigned char* mp = reinterpret_cast<const unsigned char*>(&maxPlayers);
        buffer.insert(buffer.end(), mp, mp + sizeof(int32_t));

        int32_t currentPlayers = htonl(gameInfo.currentPlayers);
        const unsigned char* cp = reinterpret_cast<const unsigned char*>(&currentPlayers);
        buffer.insert(buffer.end(), cp, cp + sizeof(int32_t));
    }
    return buffer;
}


std::vector<char> Serializer::serializeStartGame(const std::unique_ptr<StartGameDTO>& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::START_GAME));
    return buffer;
}

void Serializer::sendId(int32_t id, bool& wasClosed) {
    std::cout << "Sending id" << std::endl;
    int32_t idToSend = htonl(id);
    std::cout << "Id to send: " << idToSend << std::endl;
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&idToSend);
    socket->sendall(p, sizeof(int32_t), &wasClosed);
}

std::vector<char> Serializer::serializePlayerDTO(const std::unique_ptr<PlayerDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getPlayerId()));
    buffer.push_back(static_cast<char>(dto->getDamage()));
    buffer.push_back(static_cast<char>(dto->getHealth()));
    buffer.push_back(static_cast<char>(dto->getSpeed()));
    buffer.push_back(static_cast<char>(dto->getRespawnTime()));
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    // buffer.push_back(static_cast<char>(dto->getCurrentWeapon()));
    return buffer;
}

std::vector<char> Serializer::serializeEnemyDTO(const std::unique_ptr<EnemyDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getEnemyId()));
    buffer.push_back(static_cast<char>(dto->getDamage()));
    buffer.push_back(static_cast<char>(dto->getHealth()));
    buffer.push_back(static_cast<char>(dto->getSpeed()));
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    return buffer;
}

std::vector<char> Serializer::serializeBulletDTO(const std::unique_ptr<BulletDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getBulletId()));
    buffer.push_back(static_cast<char>(dto->getDamage()));
    buffer.push_back(static_cast<char>(dto->getSpeed()));
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    return buffer;
}

std::vector<char> Serializer::serializeItemDTO(const std::unique_ptr<ItemDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    return buffer;
}


std::vector<char> Serializer::serializeTileDTO(const std::unique_ptr<TileDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    return buffer;
}


std::vector<char> Serializer::serializeWeaponDTO(const std::unique_ptr<WeaponDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getWeaponId()));
    buffer.push_back(static_cast<char>(dto->getDamage()));
    buffer.push_back(static_cast<char>(dto->getAmmo()));
    buffer.push_back(static_cast<char>(dto->getShootSpeed()));
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    std::vector<char> bullet = serializeBulletDTO(dto->getBullet());
    buffer.insert(buffer.end(), bullet.begin(), bullet.end());
    return buffer;
}

void Serializer::sendGameDTO(const std::unique_ptr<GameDTO> dto, bool& wasClosed) {
    std::vector<char> buffer;


    std::vector<PlayerDTO> players = dto->getPlayers();
    for (const auto& player: players) {
        std::vector<char> playerBuffer = serializePlayerDTO(std::make_unique<PlayerDTO>(player));
        buffer.insert(buffer.end(), playerBuffer.begin(), playerBuffer.end());
    }

    std::vector<EnemyDTO> enemies = dto->getEnemies();
    for (const auto& enemy: enemies) {
        std::vector<char> enemyBuffer = serializeEnemyDTO(std::make_unique<EnemyDTO>(enemy));
        buffer.insert(buffer.end(), enemyBuffer.begin(), enemyBuffer.end());
    }

    std::vector<BulletDTO> bullets = dto->getBullets();
    for (const auto& bullet: bullets) {
        std::vector<char> bulletBuffer = serializeBulletDTO(std::make_unique<BulletDTO>(bullet));
        buffer.insert(buffer.end(), bulletBuffer.begin(), bulletBuffer.end());
    }

    std::vector<ItemDTO> items = dto->getItems();
    for (const auto& item: items) {
        std::vector<char> itemBuffer = serializeItemDTO(std::make_unique<ItemDTO>(item));
        buffer.insert(buffer.end(), itemBuffer.begin(), itemBuffer.end());
    }

    std::vector<WeaponDTO> weapons = dto->getWeapons();
    for (const auto& weapon: weapons) {
        std::vector<char> weaponBuffer = serializeWeaponDTO(std::make_unique<WeaponDTO>(weapon));
        buffer.insert(buffer.end(), weaponBuffer.begin(), weaponBuffer.end());
    }

    std::vector<TileDTO> tiles = dto->getTiles();
    for (const auto& tile: tiles) {
        std::vector<char> tileBuffer = serializeTileDTO(std::make_unique<TileDTO>(tile));
        buffer.insert(buffer.end(), tileBuffer.begin(), tileBuffer.end());
    }


    socket->sendall(buffer.data(), buffer.size(), &wasClosed);
}
