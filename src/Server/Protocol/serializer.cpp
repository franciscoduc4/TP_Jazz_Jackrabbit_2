#include "serializer.h"

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include <arpa/inet.h>

Serializer::Serializer(std::shared_ptr<Socket> socket): socket(socket) {
    std::cout << "[SERVER SERIALIZER] Serializer initialized" << std::endl;
}

void Serializer::sendCommand(const std::unique_ptr<CommandDTO> dto, bool& wasClosed) {
    DTOType type = dto->getType();
    socket->sendall(&type, sizeof(char), &wasClosed);
    std::cout << "[SERVER SERIALIZER] Sent dto type: " << (int)type << std::endl;

    Command command = dto->getCommand();
    socket->sendall(&command, sizeof(char), &wasClosed);
    std::cout << "[SERVER SERIALIZER] Sent command: " << (int)command << std::endl;
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
            std::cout << "[SERVER SERIALIZER] Start game command, no additional data to send"
                      << std::endl;
            break;
        case Command::MAPS_LIST:
            buffer = serializeMapsList(
                    std::make_unique<MapsListDTO>(static_cast<const MapsListDTO&>(*dto)));
            break;
        default:
            std::cerr << "[SERVER SERIALIZER] Unknown command, nothing to serialize" << std::endl;
            return;
    }
    if (!buffer.empty()) {
        socket->sendall(buffer.data(), buffer.size(), &wasClosed);
        std::cout << "[SERVER SERIALIZER] Sent buffer of size: " << buffer.size() << std::endl;
    }
}

std::vector<char> Serializer::serializeGameDTO(const std::unique_ptr<GameDTO> dto) {
    std::vector<char> buffer;
    std::cout << "[SERVER SERIALIZER] Serializing GameDTO" << std::endl;

    std::vector<PlayerDTO> players = dto->getPlayers();
    std::cout << "[SERVER SERIALIZER] Serializing players, count: " << players.size() << std::endl;
    for (const auto& player: players) {
        std::vector<char> playerBuffer = serializePlayerDTO(std::make_unique<PlayerDTO>(player));
        buffer.insert(buffer.end(), playerBuffer.begin(), playerBuffer.end());
    }

    std::vector<EnemyDTO> enemies = dto->getEnemies();
    std::cout << "[SERVER SERIALIZER] Serializing enemies, count: " << enemies.size() << std::endl;
    for (const auto& enemy: enemies) {
        std::vector<char> enemyBuffer = serializeEnemyDTO(std::make_unique<EnemyDTO>(enemy));
        buffer.insert(buffer.end(), enemyBuffer.begin(), enemyBuffer.end());
    }

    std::vector<BulletDTO> bullets = dto->getBullets();
    std::cout << "[SERVER SERIALIZER] Serializing bullets, count: " << bullets.size() << std::endl;
    for (const auto& bullet: bullets) {
        std::vector<char> bulletBuffer = serializeBulletDTO(std::make_unique<BulletDTO>(bullet));
        buffer.insert(buffer.end(), bulletBuffer.begin(), bulletBuffer.end());
    }

    std::vector<ItemDTO> items = dto->getItems();
    std::cout << "[SERVER SERIALIZER] Serializing items, count: " << items.size() << std::endl;
    for (const auto& item: items) {
        std::vector<char> itemBuffer = serializeItemDTO(std::make_unique<ItemDTO>(item));
        buffer.insert(buffer.end(), itemBuffer.begin(), itemBuffer.end());
    }

    std::vector<WeaponDTO> weapons = dto->getWeapons();
    std::cout << "[SERVER SERIALIZER] Serializing weapons, count: " << weapons.size() << std::endl;
    for (const auto& weapon: weapons) {
        std::vector<char> weaponBuffer = serializeWeaponDTO(std::make_unique<WeaponDTO>(weapon));
        buffer.insert(buffer.end(), weaponBuffer.begin(), weaponBuffer.end());
    }

    std::vector<TileDTO> tiles = dto->getTiles();
    std::cout << "[SERVER SERIALIZER] Serializing tiles, count: " << tiles.size() << std::endl;
    for (const auto& tile: tiles) {
        std::vector<char> tileBuffer = serializeTileDTO(std::make_unique<TileDTO>(tile));
        buffer.insert(buffer.end(), tileBuffer.begin(), tileBuffer.end());
    }

    return buffer;
}

std::vector<char> Serializer::serializeCreateGame(const std::unique_ptr<CreateGameDTO>& dto) {
    std::vector<char> buffer;
    uint32_t gameId = htonl(dto->getGameId());
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&gameId);
    std::cout << "[SERVER SERIALIZE CG] Game id: " << gameId << std::endl;
    buffer.insert(buffer.end(), p, p + sizeof(uint32_t));
    return buffer;
}

std::vector<char> Serializer::serializeJoinGame(const std::unique_ptr<JoinGameDTO>& dto) {
    std::vector<char> buffer;
    uint32_t gameId = htonl(dto->getGameId());
    const unsigned char* p1 = reinterpret_cast<const unsigned char*>(&gameId);
    buffer.insert(buffer.end(), p1, p1 + sizeof(uint32_t));
    uint8_t currentPlayers = dto->getCurrentPlayers();
    buffer.push_back(static_cast<char>(currentPlayers));
    std::cout << "[SERVER SERIALIZE JG] Game id: " << gameId
              << ", current players: " << (int)currentPlayers << std::endl;

    return buffer;
}

std::vector<char> Serializer::serializeGamesList(const std::unique_ptr<GamesListDTO>& dto) {
    std::vector<char> buffer;
    auto games = dto->getGames();
    uint32_t gamesSize = htonl(games.size());
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&gamesSize);
    buffer.insert(buffer.end(), p, p + sizeof(uint32_t));
    std::cout << "[SERVER SERIALIZE GL] Games size: " << games.size() << std::endl;
    for (const auto& [id, gameInfo]: games) {
        uint32_t gameId = htonl(id);
        const unsigned char* p = reinterpret_cast<const unsigned char*>(&gameId);
        buffer.insert(buffer.end(), p, p + sizeof(uint32_t));

        uint32_t nameLength = htonl(gameInfo.name.length());
        const unsigned char* np = reinterpret_cast<const unsigned char*>(&nameLength);
        buffer.insert(buffer.end(), np, np + sizeof(uint32_t));

        buffer.insert(buffer.end(), gameInfo.name.begin(), gameInfo.name.end());

        uint32_t maxPlayers = htonl(gameInfo.maxPlayers);
        const unsigned char* mp = reinterpret_cast<const unsigned char*>(&maxPlayers);
        buffer.insert(buffer.end(), mp, mp + sizeof(uint32_t));

        uint32_t currentPlayers = htonl(gameInfo.currentPlayers);
        const unsigned char* cp = reinterpret_cast<const unsigned char*>(&currentPlayers);
        buffer.insert(buffer.end(), cp, cp + sizeof(uint32_t));

        std::string mapName = gameInfo.mapName;
        uint32_t mapLength = htonl(mapName.length());
        buffer.insert(buffer.end(), reinterpret_cast<const unsigned char*>(&mapLength),
                      reinterpret_cast<const unsigned char*>(&mapLength) + sizeof(uint32_t));
        buffer.insert(buffer.end(), mapName.begin(), mapName.end());
    }
    return buffer;
}

void Serializer::sendId(uint32_t id, bool& wasClosed) {
    std::cout << "[SERVER SERIALIZER] Sending id" << std::endl;
    std::cout << "[SERVER SERIALIZER] Id to send: " << id << std::endl;
    uint32_t idToSend = htonl(id);
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&idToSend);
    socket->sendall(p, sizeof(uint32_t), &wasClosed);
    std::cout << "[SERVER SERIALIZER] Id sent" << std::endl;
}

std::vector<char> Serializer::serializePlayerDTO(const std::unique_ptr<PlayerDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getPlayerId()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player id: " << (int)dto->getPlayerId() << std::endl;
    buffer.push_back(static_cast<char>(dto->getDamage()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player damage: " << dto->getDamage() << std::endl;
    buffer.push_back(static_cast<char>(dto->getHealth()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player health: " << dto->getHealth() << std::endl;
    buffer.push_back(static_cast<char>(dto->getSpeed()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player speed: " << dto->getSpeed() << std::endl;
    buffer.push_back(static_cast<char>(dto->getRespawnTime()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player respawn time: " << dto->getRespawnTime() << std::endl;
    buffer.push_back(static_cast<char>(dto->getX()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player x: " << dto->getX() << std::endl;
    buffer.push_back(static_cast<char>(dto->getY()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player y: " << dto->getY() << std::endl;
    buffer.push_back(static_cast<char>(dto->getType()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player type: " << (int)dto->getType() << std::endl;
    buffer.push_back(static_cast<char>(dto->getState()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player state: " << (int)dto->getState() << std::endl;
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
    buffer.push_back(static_cast<char>(dto->getType()));
    buffer.push_back(static_cast<char>(dto->getState()));
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
    buffer.push_back(static_cast<char>(ItemType::GEM));
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
    std::cout << "[SERVER SERIALIZER] entrando" << std::endl;
    char gamedto = static_cast<char>(DTOType::GAME_DTO);
    socket->sendall(&gamedto, sizeof(char), &wasClosed);
    std::cout << "[SERVER SERIALIZER] Sending game dto" << std::endl;
    std::vector<char> buffer;

    std::cout << "[SERVER SERIALIZER] Sending players" << std::endl;
    std::vector<PlayerDTO> players = dto->getPlayers();
    buffer.push_back(static_cast<char>(players.size()));
    for (const auto& player: players) {
        std::vector<char> playerBuffer = serializePlayerDTO(std::make_unique<PlayerDTO>(player));
        std::cout << "[SERVER SERIALIZER] Player buffer size: " << playerBuffer.size() << std::endl;
        buffer.insert(buffer.end(), playerBuffer.begin(), playerBuffer.end());
    }

    std::cout << "[SERVER SERIALIZER] Sending enemies" << std::endl;
    std::vector<EnemyDTO> enemies = dto->getEnemies();
    buffer.push_back(static_cast<char>(enemies.size()));
    for (const auto& enemy: enemies) {
        std::vector<char> enemyBuffer = serializeEnemyDTO(std::make_unique<EnemyDTO>(enemy));
        buffer.insert(buffer.end(), enemyBuffer.begin(), enemyBuffer.end());
    }

    std::cout << "[SERVER SERIALIZER] Sending bullets" << std::endl;
    std::vector<BulletDTO> bullets = dto->getBullets();
    buffer.push_back(static_cast<char>(bullets.size()));
    for (const auto& bullet: bullets) {
        std::vector<char> bulletBuffer = serializeBulletDTO(std::make_unique<BulletDTO>(bullet));
        buffer.insert(buffer.end(), bulletBuffer.begin(), bulletBuffer.end());
    }

    std::cout << "[SERVER SERIALIZER] Sending items" << std::endl;
    std::vector<ItemDTO> items = dto->getItems();
    buffer.push_back(static_cast<char>(items.size()));
    for (const auto& item: items) {
        std::vector<char> itemBuffer = serializeItemDTO(std::make_unique<ItemDTO>(item));
        buffer.insert(buffer.end(), itemBuffer.begin(), itemBuffer.end());
    }

    std::cout << "[SERVER SERIALIZER] Sending weapons" << std::endl;
    std::vector<WeaponDTO> weapons = dto->getWeapons();
    buffer.push_back(static_cast<char>(weapons.size()));
    for (const auto& weapon: weapons) {
        std::vector<char> weaponBuffer = serializeWeaponDTO(std::make_unique<WeaponDTO>(weapon));
        buffer.insert(buffer.end(), weaponBuffer.begin(), weaponBuffer.end());
    }

    std::cout << "[SERVER SERIALIZER] Sending tiles" << std::endl;
    std::vector<TileDTO> tiles = dto->getTiles();
    buffer.push_back(static_cast<char>(tiles.size()));
    for (const auto& tile: tiles) {
        std::vector<char> tileBuffer = serializeTileDTO(std::make_unique<TileDTO>(tile));
        buffer.insert(buffer.end(), tileBuffer.begin(), tileBuffer.end());
    }

    socket->sendall(buffer.data(), buffer.size(), &wasClosed);
    std::cout << "[SERVER SERIALIZER] Sent game DTO buffer of size: " << buffer.size() << std::endl;
}

std::vector<char> Serializer::serializeMapsList(const std::unique_ptr<MapsListDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(Command::MAPS_LIST));
    auto maps = dto->getMapsMap();
    uint32_t mapsSize = htonl(maps.size());
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&mapsSize);
    buffer.insert(buffer.end(), p, p + sizeof(uint32_t));
    std::cout << "[SERVER SERIALIZER] Serializing maps list, maps count: " << maps.size()
              << std::endl;

    for (const auto& mapPair: maps) {
        uint32_t id = mapPair.first;
        const std::string& map = mapPair.second;

        uint32_t mapId = htonl(id);
        const unsigned char* p = reinterpret_cast<const unsigned char*>(&mapId);
        buffer.insert(buffer.end(), p, p + sizeof(uint32_t));

        uint32_t nameLength = htonl(map.length());
        const unsigned char* np = reinterpret_cast<const unsigned char*>(&nameLength);
        buffer.insert(buffer.end(), np, np + sizeof(uint32_t));

        buffer.insert(buffer.end(), map.begin(), map.end());
    }

    return buffer;
}
