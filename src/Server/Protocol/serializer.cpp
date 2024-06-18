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

void Serializer::sendId(uint8_t playerId, bool& wasClosed) {
    try {
        std::cout << "[SERVER SERIALIZER] Sending id" << std::endl;
        std::cout << "[SERVER SERIALIZER] Id to send: " << (int)playerId << std::endl;
        const unsigned char* p = reinterpret_cast<const unsigned char*>(&playerId);
        socket->sendall(p, sizeof(uint8_t), &wasClosed);
        std::cout << "[SERVER SERIALIZER] Id sent" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error in sendId: " << e.what() << std::endl;
    }
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
        case Command::MAPS_LIST:
            buffer = serializeMapsList(
                    std::make_unique<MapsListDTO>(static_cast<const MapsListDTO&>(*dto)));
            break;
        case Command::START_GAME:
            std::cout << "[SERVER SERIALIZER] Start game command, no additional data to send"
                      << std::endl;
            break;
        case Command::GAME_UPDATE:
            std::cout << "[SERVER SERIALIZER] Game update command. Preparing to send GameInfo."
                      << std::endl;
            buffer = serializeGameUpdate(
                    std::make_unique<GameUpdateDTO>(static_cast<const GameUpdateDTO&>(*dto)));
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

void Serializer::insertGameInfoToBuffer(std::vector<char>& buffer, const GameInfo& gameInfo) {
    std::cout << "[SERVER SERIALIZE] Inserting game info" << std::endl;

    uint8_t gameId = gameInfo.getGameId();
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&gameId);
    buffer.insert(buffer.end(), p, p + sizeof(uint8_t));

    uint8_t nameLength = gameInfo.name.length();
    const unsigned char* np = reinterpret_cast<const unsigned char*>(&nameLength);
    buffer.insert(buffer.end(), np, np + sizeof(uint8_t));

    buffer.insert(buffer.end(), gameInfo.name.begin(), gameInfo.name.end());

    uint8_t maxPlayers = gameInfo.maxPlayers;
    const unsigned char* mp = reinterpret_cast<const unsigned char*>(&maxPlayers);
    buffer.insert(buffer.end(), mp, mp + sizeof(uint8_t));

    uint8_t currentPlayers = gameInfo.currentPlayers;
    const unsigned char* cp = reinterpret_cast<const unsigned char*>(&currentPlayers);
    buffer.insert(buffer.end(), cp, cp + sizeof(uint8_t));

    uint8_t mapId = gameInfo.mapId;
    const unsigned char* mip = reinterpret_cast<const unsigned char*>(&mapId);
    buffer.insert(buffer.end(), mip, mip + sizeof(uint8_t));

    uint8_t mapNameLength = gameInfo.mapName.length();
    const unsigned char* mnp = reinterpret_cast<const unsigned char*>(&mapNameLength);
    buffer.insert(buffer.end(), mnp, mnp + sizeof(uint8_t));

    std::string mapName = gameInfo.mapName;
    uint8_t mapLength = mapName.length();
    buffer.insert(buffer.end(), mapName.begin(), mapName.end());
}

std::vector<char> Serializer::serializeCreateGame(const std::unique_ptr<CreateGameDTO>& dto) {
    std::vector<char> buffer;
    uint8_t gameId = dto->getGameId();
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&gameId);
    std::cout << "[SERVER SERIALIZE CG] Game id: " << gameId << std::endl;
    buffer.insert(buffer.end(), p, p + sizeof(uint8_t));
    return buffer;
}

std::vector<char> Serializer::serializeJoinGame(const std::unique_ptr<JoinGameDTO>& dto) {
    std::vector<char> buffer;
    uint8_t gameId = dto->getGameId();
    const unsigned char* p1 = reinterpret_cast<const unsigned char*>(&gameId);
    buffer.insert(buffer.end(), p1, p1 + sizeof(uint8_t));
    uint8_t currentPlayers = dto->getCurrentPlayers();
    buffer.push_back(static_cast<char>(currentPlayers));
    std::cout << "[SERVER SERIALIZE JG] Game id: " << gameId
              << ", current players: " << (int)currentPlayers << std::endl;

    return buffer;
}

std::vector<char> Serializer::serializeGamesList(const std::unique_ptr<GamesListDTO>& dto) {
    std::vector<char> buffer;
    auto games = dto->getGames();
    uint8_t gamesSize = games.size();
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&gamesSize);
    buffer.insert(buffer.end(), p, p + sizeof(uint8_t));
    std::cout << "[SERVER SERIALIZE GL] Games size: " << games.size() << std::endl;
    for (const auto& [gameId, gameInfo]: games) {
        const unsigned char* p = reinterpret_cast<const unsigned char*>(&gameId);
        buffer.insert(buffer.end(), p, p + sizeof(uint8_t));

        insertGameInfoToBuffer(buffer, gameInfo);
    }
    return buffer;
}

std::vector<char> Serializer::serializeMapsList(const std::unique_ptr<MapsListDTO> dto) {
    std::vector<char> buffer;
    auto maps = dto->getMapsMap();
    uint8_t mapsSize = maps.size();
    const auto* sizeMaps = reinterpret_cast<const unsigned char*>(&mapsSize);
    buffer.insert(buffer.end(), sizeMaps, sizeMaps + sizeof(uint8_t));
    std::cout << "[SERVER SERIALIZE ML] Inserted maps size: " << (int)maps.size() << std::endl;

    for (const auto& [mapId, name]: maps) {
        const unsigned char* p = reinterpret_cast<const unsigned char*>(&mapId);
        buffer.insert(buffer.end(), p, p + sizeof(uint8_t));
        std::cout << "[SERVER SERIALIZE ML] Inserted map ID: " << (int)mapId << std::endl;

        uint8_t nameLength = name.length();
        const unsigned char* np = reinterpret_cast<const unsigned char*>(&nameLength);
        buffer.insert(buffer.end(), np, np + sizeof(uint8_t));
        std::cout << "[SERVER SERIALIZE ML] Inserted name length: " << (int)nameLength << std::endl;

        buffer.insert(buffer.end(), name.begin(), name.end());
        std::cout << "[SERVER SERIALIZE ML] Inserted map name: " << name << std::endl;
    }

    return buffer;
}

std::vector<char> Serializer::serializeGameUpdate(const std::unique_ptr<GameUpdateDTO>& dto) {
    std::cout << "[SERVER SERIALIZER GU] Serializing game update" << std::endl;
    std::vector<char> buffer;
    GameInfo gameInfo = dto->getGameInfo();
    insertGameInfoToBuffer(buffer, gameInfo);
    return buffer;
}

std::vector<char> Serializer::serializePlayerDTO(const std::unique_ptr<PlayerDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getPlayerId()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player id: " << (int)dto->getPlayerId()
              << std::endl;
    buffer.push_back(static_cast<char>(dto->getDamage()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player damage: " << dto->getDamage()
              << std::endl;
    buffer.push_back(static_cast<char>(dto->getHealth()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player health: " << dto->getHealth()
              << std::endl;
    buffer.push_back(static_cast<char>(dto->getSpeed()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player speed: " << dto->getSpeed()
              << std::endl;
    buffer.push_back(static_cast<char>(dto->getRespawnTime()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player respawn time: "
              << dto->getRespawnTime() << std::endl;
    buffer.push_back(static_cast<char>(dto->getX()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player x: " << (int)dto->getX()
              << std::endl;
    buffer.push_back(static_cast<char>(dto->getY()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player y: " << (int)dto->getY()
              << std::endl;
    buffer.push_back(static_cast<char>(dto->getType()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player type: " << (int)dto->getType()
              << std::endl;
    buffer.push_back(static_cast<char>(dto->getState()));
    std::cout << "[SERVER SERIALIZER PLAYER] Serializing player state: " << (int)dto->getState()
              << std::endl;
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
    std::cout << "[SERVER SERIALIZER ENEMY] Serialized enemy with id: " << (int)dto->getEnemyId()
              << std::endl;
    return buffer;
}

std::vector<char> Serializer::serializeBulletDTO(const std::unique_ptr<BulletDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getBulletId()));
    buffer.push_back(static_cast<char>(dto->getDamage()));
    buffer.push_back(static_cast<char>(dto->getSpeed()));
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    std::cout << "[SERVER SERIALIZER BULLET] Serialized bullet with id: " << (int)dto->getBulletId()
              << std::endl;
    return buffer;
}

std::vector<char> Serializer::serializeItemDTO(const std::unique_ptr<ItemDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    buffer.push_back(static_cast<char>(ItemType::GEM));
    std::cout << "[SERVER SERIALIZER ITEM] Serialized item at position: (" << (int)dto->getX()
              << ", " << (int)dto->getY() << ")" << std::endl;
    return buffer;
}

std::vector<char> Serializer::serializeTileDTO(const std::unique_ptr<TileDTO> dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getX()));
    buffer.push_back(static_cast<char>(dto->getY()));
    std::cout << "[SERVER SERIALIZER TILE] Serialized tile at position: (" << (int)dto->getX()
              << ", " << (int)dto->getY() << ")" << std::endl;
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
    std::cout << "[SERVER SERIALIZER WEAPON] Serialized weapon with id: " << (int)dto->getWeaponId()
              << std::endl;
    return buffer;
}

void Serializer::sendGameDTO(const std::unique_ptr<GameDTO> dto, bool& wasClosed) {
    std::cout << "[SERVER SERIALIZER] Sending game DTO" << std::endl;
    char gamedto = static_cast<char>(DTOType::GAME_DTO);
    socket->sendall(&gamedto, sizeof(char), &wasClosed);
    std::vector<char> buffer;

    std::cout << "[SERVER SERIALIZER] Sending players" << std::endl;
    std::vector<PlayerDTO> players = dto->getPlayers();
    std::cout << "[SERVER SERIALIZER] Players size: " << players.size() << std::endl;
    buffer.push_back(static_cast<char>(players.size()));
    for (const auto& player: players) {
        std::vector<char> playerBuffer = serializePlayerDTO(std::make_unique<PlayerDTO>(player));
        std::cout << "[SERVER SERIALIZER] Player buffer size: " << playerBuffer.size() << std::endl;
        buffer.insert(buffer.end(), playerBuffer.begin(), playerBuffer.end());
    }

    std::cout << "[SERVER SERIALIZER] Sending enemies" << std::endl;
    std::vector<EnemyDTO> enemies = dto->getEnemies();
    std::cout << "[SERVER SERIALIZER] Enemies size: " << enemies.size() << std::endl;
    buffer.push_back(static_cast<char>(enemies.size()));
    for (const auto& enemy: enemies) {
        std::vector<char> enemyBuffer = serializeEnemyDTO(std::make_unique<EnemyDTO>(enemy));
        buffer.insert(buffer.end(), enemyBuffer.begin(), enemyBuffer.end());
    }

    std::cout << "[SERVER SERIALIZER] Sending bullets" << std::endl;
    std::vector<BulletDTO> bullets = dto->getBullets();
    std::cout << "[SERVER SERIALIZER] Bullets size: " << bullets.size() << std::endl;
    buffer.push_back(static_cast<char>(bullets.size()));
    for (const auto& bullet: bullets) {
        std::vector<char> bulletBuffer = serializeBulletDTO(std::make_unique<BulletDTO>(bullet));
        buffer.insert(buffer.end(), bulletBuffer.begin(), bulletBuffer.end());
    }

    std::cout << "[SERVER SERIALIZER] Sending items" << std::endl;
    std::vector<ItemDTO> items = dto->getItems();
    std::cout << "[SERVER SERIALIZER] Items size: " << items.size() << std::endl;
    buffer.push_back(static_cast<char>(items.size()));
    for (const auto& item: items) {
        std::vector<char> itemBuffer = serializeItemDTO(std::make_unique<ItemDTO>(item));
        buffer.insert(buffer.end(), itemBuffer.begin(), itemBuffer.end());
    }

    std::cout << "[SERVER SERIALIZER] Sending weapons" << std::endl;
    std::vector<WeaponDTO> weapons = dto->getWeapons();
    std::cout << "[SERVER SERIALIZER] Weapons size: " << weapons.size() << std::endl;
    buffer.push_back(static_cast<char>(weapons.size()));
    for (const auto& weapon: weapons) {
        std::vector<char> weaponBuffer = serializeWeaponDTO(std::make_unique<WeaponDTO>(weapon));
        buffer.insert(buffer.end(), weaponBuffer.begin(), weaponBuffer.end());
    }

    std::cout << "[SERVER SERIALIZER] Sending tiles" << std::endl;
    std::vector<TileDTO> tiles = dto->getTiles();
    std::cout << "[SERVER SERIALIZER] Tiles size: " << tiles.size() << std::endl;
    buffer.push_back(static_cast<char>(tiles.size()));
    for (const auto& tile: tiles) {
        std::vector<char> tileBuffer = serializeTileDTO(std::make_unique<TileDTO>(tile));
        buffer.insert(buffer.end(), tileBuffer.begin(), tileBuffer.end());
    }

    socket->sendall(buffer.data(), buffer.size(), &wasClosed);
    std::cout << "[SERVER SERIALIZER] Sent game DTO buffer of size: " << buffer.size() << std::endl;
}
