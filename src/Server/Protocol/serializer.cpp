#include "serializer.h"

#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include <arpa/inet.h>

Serializer::Serializer(const std::shared_ptr<Socket>& socket, std::atomic<bool>& keepPlaying,
                       std::atomic<bool>& inGame):
        socket(socket), keepPlaying(keepPlaying), inGame(inGame), wasClosed(false) {
    // std::cout << "[SERVER SERIALIZER] Serializer initialized" << std::endl;
}

void Serializer::clientClosed() {
    // std::cerr << "[SERVER SERIALIZER] Client closed connection" << std::endl;
    this->keepPlaying.store(false);
    this->inGame.store(false);
}

void Serializer::sendId(uint8_t playerId) {
    try {
        // std::cout << "[SERVER SERIALIZER] Sending id" << std::endl;
        std::cout << "[SERVER SERIALIZER] Id to send: " << (int)playerId << std::endl;
        const auto* p = reinterpret_cast<const unsigned char*>(&playerId);
        socket->sendall(p, sizeof(uint8_t), &wasClosed);
        if (wasClosed) {
            this->clientClosed();
            return;
        }
        // std::cout << "[SERVER SERIALIZER] Id sent" << std::endl;
    } catch (const std::exception& e) {
        // std::cerr << "[SERVER SERIALIZER] Error in sendId: " << e.what() << std::endl;
    }
}

// ------------------------ LOBBY ------------------------
void Serializer::sendCommand(const std::unique_ptr<CommandDTO>& dto) {
    // std::cout << "[SERVER SERIALIZER] Sending DTO Type" << std::endl;
    DTOType type = dto->getType();
    socket->sendall(&type, sizeof(char), &wasClosed);
    if (wasClosed) {
        this->clientClosed();
        return;
    }
    // std::cout << "[SERVER SERIALIZER] Sent dto type: " << (int)type << std::endl;

    // std::cout << "[SERVER SERIALIZER] Sending command" << std::endl;
    Command command = dto->getCommand();
    socket->sendall(&command, sizeof(char), &wasClosed);
    if (wasClosed) {
        this->clientClosed();
        return;
    }
    // std::cout << "[SERVER SERIALIZER] Sent command: " << (int)command << std::endl;
    std::vector<char> buffer;

    switch (command) {
        case Command::CREATE_GAME:
            // std::cout << "[SERVER SERIALIZER] Create game command, preparing to send game id"
            //   << std::endl;
            buffer = serializeCreateGame(
                    std::make_unique<CreateGameDTO>(dynamic_cast<const CreateGameDTO&>(*dto)));
            break;
        case Command::JOIN_GAME:
            // std::cout << "[SERVER SERIALIZER] Join game command, preparing to send game id"
            //   << std::endl;
            buffer = serializeJoinGame(
                    std::make_unique<JoinGameDTO>(dynamic_cast<const JoinGameDTO&>(*dto)));
            break;
        case Command::GAMES_LIST:
            // std::cout << "[SERVER SERIALIZER] Games list command, preparing to send games list"
            //   << std::endl;
            buffer = serializeGamesList(
                    std::make_unique<GamesListDTO>(dynamic_cast<const GamesListDTO&>(*dto)));
            break;
        case Command::MAPS_LIST:
            // std::cout << "[SERVER SERIALIZER] Maps list command, preparing to send maps list"
            //   << std::endl;
            buffer = serializeMapsList(
                    std::make_unique<MapsListDTO>(dynamic_cast<const MapsListDTO&>(*dto)));
            break;
        case Command::START_GAME:
            // std::cout << "[SERVER SERIALIZER] Start game command, no additional data to send"
            //   << std::endl;
            inGame.store(true);
            break;
        case Command::GAME_UPDATE:
            // std::cout << "[SERVER SERIALIZER] Game update command. Preparing to send GameInfo."
            //   << std::endl;
            buffer = serializeGameUpdate(
                    std::make_unique<GameUpdateDTO>(dynamic_cast<const GameUpdateDTO&>(*dto)));
            break;
        default:
            // std::cerr << "[SERVER SERIALIZER] Unknown command, nothing to serialize" <<
            // std::endl;
            return;
    }
    if (!buffer.empty()) {
        socket->sendall(buffer.data(), buffer.size(), &wasClosed);
        if (wasClosed) {
            this->clientClosed();
            return;
        }
        // std::cout << "[SERVER SERIALIZER] Sent buffer of size: " << buffer.size() << std::endl;
    } else {
        // std::cout << "[SERVER SERIALIZER] Buffer is empty, nothing to send" << std::endl;
    }
}

void Serializer::insertGameInfoIntoBuffer(std::vector<char>& buffer, const GameInfo& gameInfo) {
    std::cout << "[SERVER SERIALIZE] Inserting game info" << std::endl;

    uint8_t gameId = gameInfo.getGameId();
    const auto* p = reinterpret_cast<const unsigned char*>(&gameId);
    buffer.insert(buffer.end(), p, p + sizeof(uint8_t));

    uint8_t nameLength = gameInfo.name.length();
    const auto* np = reinterpret_cast<const unsigned char*>(&nameLength);
    buffer.insert(buffer.end(), np, np + sizeof(uint8_t));

    buffer.insert(buffer.end(), gameInfo.name.begin(), gameInfo.name.end());

    uint8_t maxPlayers = gameInfo.maxPlayers;
    const auto* mp = reinterpret_cast<const unsigned char*>(&maxPlayers);
    buffer.insert(buffer.end(), mp, mp + sizeof(uint8_t));

    uint8_t currentPlayers = gameInfo.currentPlayers;
    const auto* cp = reinterpret_cast<const unsigned char*>(&currentPlayers);
    buffer.insert(buffer.end(), cp, cp + sizeof(uint8_t));

    uint8_t mapId = gameInfo.mapId;
    const auto* mip = reinterpret_cast<const unsigned char*>(&mapId);
    buffer.insert(buffer.end(), mip, mip + sizeof(uint8_t));

    uint8_t mapNameLength = gameInfo.mapName.length();
    const auto* mnp = reinterpret_cast<const unsigned char*>(&mapNameLength);
    buffer.insert(buffer.end(), mnp, mnp + sizeof(uint8_t));

    std::string mapName = gameInfo.mapName;
    buffer.insert(buffer.end(), mapName.begin(), mapName.end());
}

std::vector<char> Serializer::serializeCreateGame(const std::unique_ptr<CreateGameDTO>& dto) {
    std::vector<char> buffer;
    uint8_t gameId = dto->getGameId();
    const auto* p = reinterpret_cast<const unsigned char*>(&gameId);
    std::cout << "[SERVER SERIALIZE CG] Game id: " << (int)gameId << std::endl;
    buffer.insert(buffer.end(), p, p + sizeof(uint8_t));
    return buffer;
}

std::vector<char> Serializer::serializeJoinGame(const std::unique_ptr<JoinGameDTO>& dto) {
    std::vector<char> buffer;
    std::cout << "[SERVER SERIALIZE JG] Serializing join game" << std::endl;
    uint8_t gameId = dto->getGameId();
    std::cout << "[SERVER SERIALIZE JG] Game id: " << static_cast<int>(gameId) << std::endl;
    const auto* p1 = reinterpret_cast<const unsigned char*>(&gameId);
    buffer.insert(buffer.end(), p1, p1 + sizeof(uint8_t));
    std::cout << "[SERVER SERIALIZE JG] Inserted game id" << std::endl;
    uint8_t currentPlayers = dto->getCurrentPlayers();
    std::cout << "[SERVER SERIALIZE JG] Current players: " << (int)currentPlayers << std::endl;
    buffer.push_back(static_cast<char>(currentPlayers));
    std::cout << "[SERVER SERIALIZE JG] Game id: " << gameId
              << ", current players: " << (int)currentPlayers << std::endl;

    return buffer;
}

std::vector<char> Serializer::serializeGamesList(const std::unique_ptr<GamesListDTO>& dto) {
    std::vector<char> buffer;
    auto games = dto->getGames();
    uint8_t gamesSize = games.size();
    const auto* p = reinterpret_cast<const unsigned char*>(&gamesSize);
    buffer.insert(buffer.end(), p, p + sizeof(uint8_t));
    std::cout << "[SERVER SERIALIZE GL] Games size: " << games.size() << std::endl;
    for (const auto& [gameId, gameInfo]: games) {
        insertGameInfoIntoBuffer(buffer, gameInfo);
    }
    return buffer;
}

std::vector<char> Serializer::serializeMapsList(const std::unique_ptr<MapsListDTO>& dto) {
    std::vector<char> buffer;
    auto maps = dto->getMapsMap();
    uint8_t mapsSize = maps.size();
    const auto* sizeMaps = reinterpret_cast<const unsigned char*>(&mapsSize);
    buffer.insert(buffer.end(), sizeMaps, sizeMaps + sizeof(uint8_t));
    std::cout << "[SERVER SERIALIZE ML] Inserted maps size: " << (int)maps.size() << std::endl;

    for (const auto& [mapId, name]: maps) {
        const auto* p = reinterpret_cast<const unsigned char*>(&mapId);
        buffer.insert(buffer.end(), p, p + sizeof(uint8_t));
        std::cout << "[SERVER SERIALIZE ML] Inserted map ID: " << (int)mapId << std::endl;

        uint8_t nameLength = name.length();
        const auto* np = reinterpret_cast<const unsigned char*>(&nameLength);
        buffer.insert(buffer.end(), np, np + sizeof(uint8_t));
        std::cout << "[SERVER SERIALIZE ML] Inserted name length: " << (int)nameLength << std::endl;

        buffer.insert(buffer.end(), name.begin(), name.end());
        std::cout << "[SERVER SERIALIZE ML] Inserted map name: " << name << std::endl;
    }

    return buffer;
}

std::vector<char> Serializer::serializeGameUpdate(const std::unique_ptr<GameUpdateDTO>& dto) {
    // std::cout << "[SERVER SERIALIZER GU] Serializing game update" << std::endl;
    std::vector<char> buffer;
    GameInfo gameInfo = dto->getGameInfo();
    insertGameInfoIntoBuffer(buffer, gameInfo);
    return buffer;
}

// -------------------------- GAME -----------------------------------
void Serializer::insertPositionIntoBuffer(std::vector<char>& buffer, const uint32_t& x,
                                          const uint32_t& y) {
    uint32_t x_network = htonl(x);
    const auto* xp = reinterpret_cast<const unsigned char*>(&x_network);
    buffer.insert(buffer.end(), xp, xp + sizeof(uint32_t));

    uint32_t y_network = htonl(y);
    const auto* yp = reinterpret_cast<const unsigned char*>(&y_network);
    buffer.insert(buffer.end(), yp, yp + sizeof(uint32_t));
}

void Serializer::insert_int_into_buffer(std::vector<char>& buffer, const int& value) {
    uint32_t network_value = htonl(value);
    const auto* p = reinterpret_cast<const unsigned char*>(&network_value);
    buffer.insert(buffer.end(), p, p + sizeof(uint32_t));
}

std::vector<char> Serializer::serializePlayerDTO(const std::unique_ptr<PlayerDTO>& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getPlayerId()));
    // std::cout << "[SERVER SERIALIZER PLAYER] Serializing player id: " << (int)dto->getPlayerId()
    //   << std::endl;
    // Serializer::insert_int_into_buffer(buffer, dto->getDamage());
    buffer.push_back(static_cast<char>(dto->getDamage()));
    // std::cout << "[SERVER SERIALIZER PLAYER] Serializing player damage: " << dto->getDamage()
    //   << std::endl;
    // Serializer::insert_int_into_buffer(buffer, dto->getHealth());
    buffer.push_back(static_cast<char>(dto->getHealth()));
    // std::cout << "[SERVER SERIALIZER PLAYER] Serializing player health: " << dto->getHealth()
    //   << std::endl;
    // Serializer::insert_int_into_buffer(buffer, dto->getSpeed());
    buffer.push_back(static_cast<char>(dto->getSpeed()));
    // std::cout << "[SERVER SERIALIZER PLAYER] Serializing player speed: " << dto->getSpeed()
    //   << std::endl;
    // Serializer::insert_int_into_buffer(buffer, dto->getRespawnTime());
    buffer.push_back(static_cast<char>(dto->getRespawnTime()));
    // std::cout << "[SERVER SERIALIZER PLAYER] Serializing player respawn time: "
    // << dto->getRespawnTime() << std::endl;
    Serializer::insertPositionIntoBuffer(buffer, dto->getX(), dto->getY());
    buffer.push_back(static_cast<char>(dto->getCharacterType()));
    // std::cout << "[SERVER SERIALIZER PLAYER] Serializing player type: " <<
    // (int)dto->getCharacterType()
    //   << std::endl;
    buffer.push_back(static_cast<char>(dto->getState()));
    // std::cout << "[SERVER SERIALIZER PLAYER] Serializing player state: " << (int)dto->getState()
    //   << std::endl;
    Serializer::insert_int_into_buffer(buffer, dto->getScore());
    return buffer;
}

std::vector<char> Serializer::serializeEnemyDTO(const std::unique_ptr<EnemyDTO>& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getEnemyId()));
    // Serializer::insert_int_into_buffer(buffer, dto->getDamage());
    buffer.push_back(static_cast<char>(dto->getDamage()));

    // Serializer::insert_int_into_buffer(buffer, dto->getHealth());
    buffer.push_back(static_cast<char>(dto->getHealth()));

    // Serializer::insert_int_into_buffer(buffer, dto->getSpeed());
    buffer.push_back(static_cast<char>(dto->getSpeed()));

    Serializer::insertPositionIntoBuffer(buffer, dto->getX(), dto->getY());
    buffer.push_back(static_cast<char>(dto->getEnemyType()));
    buffer.push_back(static_cast<char>(dto->getState()));
    // std::cout << "[SERVER SERIALIZER ENEMY] Serialized enemy with id: " << (int)dto->getEnemyId()
    //   << std::endl;
    return buffer;
}

std::vector<char> Serializer::serializeBulletDTO(const std::unique_ptr<BulletDTO>& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getBulletId()));
    Serializer::insert_int_into_buffer(buffer, dto->getDamage());
    Serializer::insert_int_into_buffer(buffer, dto->getSpeed());
    Serializer::insertPositionIntoBuffer(buffer, dto->getX(), dto->getY());
    Serializer::insert_int_into_buffer(buffer, dto->getShooterId());
    // std::cout << "[SERVER SERIALIZER BULLET] Serialized bullet with id: " <<
    // (int)dto->getBulletId()
    //   << std::endl;
    return buffer;
}

std::vector<char> Serializer::serializeItemDTO(const std::unique_ptr<ItemDTO>& dto) {
    std::vector<char> buffer;
    Serializer::insertPositionIntoBuffer(buffer, dto->getX(), dto->getY());
    buffer.push_back(static_cast<char>(dto->getItemType()));
    // std::cout << "[SERVER SERIALIZER ITEM] Serialized item at position: (" << (int)dto->getX()
    // << ", " << (int)dto->getY() << ")" << std::endl;
    return buffer;
}

std::vector<char> Serializer::serializeTileDTO(const std::unique_ptr<TileDTO>& dto) {
    std::vector<char> buffer;
    Serializer::insertPositionIntoBuffer(buffer, dto->getX(), dto->getY());

    // Serializar el tipo de ObstacleType
    ObstacleType type = dto->getObstacleType();
    buffer.push_back(static_cast<char>(type));

    // std::cout << "[SERVER SERIALIZER TILE] Serialized tile at position: (" << (int)dto->getX()
    // << ", " << (int)dto->getY() << "), Type: " << static_cast<int>(type) << std::endl;

    return buffer;
}


std::vector<char> Serializer::serializeWeaponDTO(const std::unique_ptr<WeaponDTO>& dto) {
    std::vector<char> buffer;
    buffer.push_back(static_cast<char>(dto->getWeaponId()));
    Serializer::insert_int_into_buffer(buffer, dto->getDamage());
    Serializer::insert_int_into_buffer(buffer, dto->getAmmo());
    Serializer::insert_int_into_buffer(buffer, dto->getShootSpeed());
    Serializer::insertPositionIntoBuffer(buffer, dto->getX(), dto->getY());
    std::vector<char> bullet = serializeBulletDTO(dto->getBullet());
    buffer.insert(buffer.end(), bullet.begin(), bullet.end());
    // std::cout << "[SERVER SERIALIZER WEAPON] Serialized weapon with id: " <<
    // (int)dto->getWeaponId()
    //   << std::endl;
    return buffer;
}

void Serializer::sendGameDTO(const std::unique_ptr<GameDTO>& dto) {
    // std::cout << "[SERVER SERIALIZER] Sending game DTO" << std::endl;
    char gamedto = static_cast<char>(DTOType::GAME_DTO);
    socket->sendall(&gamedto, sizeof(char), &wasClosed);
    if (wasClosed) {
        this->clientClosed();
        return;
    }
    std::vector<char> buffer;

    // std::cout << "[SERVER SERIALIZER] Sending players" << std::endl;
    std::vector<PlayerDTO> players = dto->getPlayers();
    // std::cout << "[SERVER SERIALIZER] Players size: " << players.size() << std::endl;
    // std::vector.size() devuelve size_t que es dependiente de la plataforma
    // No vamos a tener más del rango de int así que casteo a uint32_t e inserto ese tipo al buffer.
    // buffer.push_back(static_cast<char>(players.size()));
    Serializer::insert_int_into_buffer(buffer, static_cast<int>(players.size()));
    for (const auto& player: players) {
        std::vector<char> playerBuffer = serializePlayerDTO(std::make_unique<PlayerDTO>(player));
        // std::cout << "[SERVER SERIALIZER] Player buffer size: " << playerBuffer.size() <<
        // std::endl;
        buffer.insert(buffer.end(), playerBuffer.begin(), playerBuffer.end());
    }

    // std::cout << "[SERVER SERIALIZER] Sending enemies" << std::endl;
    std::vector<EnemyDTO> enemies = dto->getEnemies();
    // std::cout << "[SERVER SERIALIZER] Enemies size: " << enemies.size() << std::endl;
    // buffer.push_back(static_cast<char>(enemies.size()));
    // Ídem anterior
    Serializer::insert_int_into_buffer(buffer, static_cast<int>(enemies.size()));
    for (const auto& enemy: enemies) {
        std::vector<char> enemyBuffer = serializeEnemyDTO(std::make_unique<EnemyDTO>(enemy));
        buffer.insert(buffer.end(), enemyBuffer.begin(), enemyBuffer.end());
    }

    // std::cout << "[SERVER SERIALIZER] Sending bullets" << std::endl;
    std::vector<BulletDTO> bullets = dto->getBullets();
    // std::cout << "[SERVER SERIALIZER] Bullets size: " << bullets.size() << std::endl;
    // buffer.push_back(static_cast<char>(bullets.size()));
    Serializer::insert_int_into_buffer(buffer, static_cast<int>(bullets.size()));
    for (const auto& bullet: bullets) {
        std::vector<char> bulletBuffer = serializeBulletDTO(std::make_unique<BulletDTO>(bullet));
        buffer.insert(buffer.end(), bulletBuffer.begin(), bulletBuffer.end());
    }

    // std::cout << "[SERVER SERIALIZER] Sending items" << std::endl;
    std::vector<ItemDTO> items = dto->getItems();
    // std::cout << "[SERVER SERIALIZER] Items size: " << items.size() << std::endl;
    // buffer.push_back(static_cast<char>(items.size()));
    Serializer::insert_int_into_buffer(buffer, static_cast<int>(items.size()));
    for (const auto& item: items) {
        std::vector<char> itemBuffer = serializeItemDTO(std::make_unique<ItemDTO>(item));
        buffer.insert(buffer.end(), itemBuffer.begin(), itemBuffer.end());
    }

    // std::cout << "[SERVER SERIALIZER] Sending weapons" << std::endl;
    std::vector<WeaponDTO> weapons = dto->getWeapons();
    // std::cout << "[SERVER SERIALIZER] Weapons size: " << weapons.size() << std::endl;
    // buffer.push_back(static_cast<char>(weapons.size()));
    Serializer::insert_int_into_buffer(buffer, static_cast<int>(weapons.size()));
    for (const auto& weapon: weapons) {
        std::vector<char> weaponBuffer = serializeWeaponDTO(std::make_unique<WeaponDTO>(weapon));
        buffer.insert(buffer.end(), weaponBuffer.begin(), weaponBuffer.end());
    }

    // std::cout << "[SERVER SERIALIZER] Sending tiles" << std::endl;
    std::vector<TileDTO> tiles = dto->getTiles();
    // std::cout << "[SERVER SERIALIZER] Tiles size: " << tiles.size() << std::endl;
    // buffer.push_back(static_cast<char>(tiles.size()));
    Serializer::insert_int_into_buffer(buffer, static_cast<int>(tiles.size()));
    for (const auto& tile: tiles) {
        std::vector<char> tileBuffer = serializeTileDTO(std::make_unique<TileDTO>(tile));
        buffer.insert(buffer.end(), tileBuffer.begin(), tileBuffer.end());
    }

    socket->sendall(buffer.data(), buffer.size(), &wasClosed);
    if (wasClosed) {
        this->clientClosed();
        return;
    }
    // std::cout << "[SERVER SERIALIZER] Sent game DTO buffer of size: " << buffer.size() <<
    // std::endl;
}
