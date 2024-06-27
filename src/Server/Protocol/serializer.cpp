#include "serializer.h"

#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include <arpa/inet.h>

#include "protocol.h"

/*
 * Constructor por defecto de Serializer.
 */
Serializer::Serializer() {}

/*
 * Constructor de Serializer.
 * Inicializa el protocolo con el socket, keepPlaying y inGame.
 */
Serializer::Serializer(const std::shared_ptr<Socket>& socket, std::atomic<bool>& keepPlaying,
                       std::atomic<bool>& inGame):
        protocol(std::make_shared<Protocol>(socket, keepPlaying, inGame)) {}

/*
 * Envía el ID del jugador a través del protocolo.
 */
void Serializer::sendId(uint8_t playerId) {
    try {
        protocol->sendId(playerId);
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error sending id" << std::endl;
    }
}

/*
 * Envía un comando a través del protocolo.
 * Determina el tipo de comando y lo serializa apropiadamente.
 */
void Serializer::sendCommand(const std::unique_ptr<CommandDTO>& dto) {
    try {
        DTOType type = dto->getType();
        protocol->sendDTOType(static_cast<char>(type));

        Command command = dto->getCommand();
        protocol->sendDTOType(static_cast<char>(command));

        std::vector<char> buffer;

        switch (command) {
            case Command::CREATE_GAME:
                buffer = serializeCreateGame(
                        std::make_unique<CreateGameDTO>(dynamic_cast<const CreateGameDTO&>(*dto)));
                break;
            case Command::JOIN_GAME:
                buffer = serializeJoinGame(
                        std::make_unique<JoinGameDTO>(dynamic_cast<const JoinGameDTO&>(*dto)));
                break;
            case Command::GAMES_LIST:
                buffer = serializeGamesList(
                        std::make_unique<GamesListDTO>(dynamic_cast<const GamesListDTO&>(*dto)));
                break;
            case Command::MAPS_LIST:
                buffer = serializeMapsList(
                        std::make_unique<MapsListDTO>(dynamic_cast<const MapsListDTO&>(*dto)));
                break;
            case Command::START_GAME:
                protocol->setInGame(true);
                break;
            case Command::GAME_UPDATE:
                buffer = serializeGameUpdate(
                        std::make_unique<GameUpdateDTO>(dynamic_cast<const GameUpdateDTO&>(*dto)));
                break;
            default:
                return;
        }
        if (!buffer.empty()) {
            protocol->sendData(buffer);
        }
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error sending command" << std::endl;
    }
}

/*
 * Inserta información de un juego en un buffer.
 */
void Serializer::insertGameInfoIntoBuffer(std::vector<char>& buffer, const GameInfo& gameInfo) {
    try {
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
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error inserting game info into buffer" << std::endl;
    }
}

/*
 * Serializa un DTO de creación de juego en un buffer.
 */
std::vector<char> Serializer::serializeCreateGame(const std::unique_ptr<CreateGameDTO>& dto) {
    std::vector<char> buffer;
    try {
        uint8_t gameId = dto->getGameId();
        const auto* p = reinterpret_cast<const unsigned char*>(&gameId);
        buffer.insert(buffer.end(), p, p + sizeof(uint8_t));
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error serializing create game" << std::endl;
    }
    return buffer;
}

/*
 * Serializa un DTO de unión a juego en un buffer.
 */
std::vector<char> Serializer::serializeJoinGame(const std::unique_ptr<JoinGameDTO>& dto) {
    std::vector<char> buffer;
    try {
        uint8_t gameId = dto->getGameId();
        const auto* p1 = reinterpret_cast<const unsigned char*>(&gameId);
        buffer.insert(buffer.end(), p1, p1 + sizeof(uint8_t));
        uint8_t currentPlayers = dto->getCurrentPlayers();
        buffer.push_back(static_cast<char>(currentPlayers));
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error serializing join game" << std::endl;
    }
    return buffer;
}

/*
 * Serializa un DTO de lista de juegos en un buffer.
 */
std::vector<char> Serializer::serializeGamesList(const std::unique_ptr<GamesListDTO>& dto) {
    std::vector<char> buffer;
    try {
        auto games = dto->getGames();
        uint8_t gamesSize = games.size();
        const auto* p = reinterpret_cast<const unsigned char*>(&gamesSize);
        buffer.insert(buffer.end(), p, p + sizeof(uint8_t));
        for (const auto& [gameId, gameInfo]: games) {
            insertGameInfoIntoBuffer(buffer, gameInfo);
        }
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error serializing games list" << std::endl;
    }
    return buffer;
}

/*
 * Serializa un DTO de lista de mapas en un buffer.
 */
std::vector<char> Serializer::serializeMapsList(const std::unique_ptr<MapsListDTO>& dto) {
    std::vector<char> buffer;
    try {
        auto maps = dto->getMapsMap();
        uint8_t mapsSize = maps.size();
        const auto* sizeMaps = reinterpret_cast<const unsigned char*>(&mapsSize);
        buffer.insert(buffer.end(), sizeMaps, sizeMaps + sizeof(uint8_t));

        for (const auto& [mapId, name]: maps) {
            const auto* p = reinterpret_cast<const unsigned char*>(&mapId);
            buffer.insert(buffer.end(), p, p + sizeof(uint8_t));

            uint8_t nameLength = name.length();
            const auto* np = reinterpret_cast<const unsigned char*>(&nameLength);
            buffer.insert(buffer.end(), np, np + sizeof(uint8_t));

            buffer.insert(buffer.end(), name.begin(), name.end());
        }
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error serializing maps list" << std::endl;
    }
    return buffer;
}

/*
 * Serializa un DTO de actualización de juego en un buffer.
 */
std::vector<char> Serializer::serializeGameUpdate(const std::unique_ptr<GameUpdateDTO>& dto) {
    std::vector<char> buffer;
    try {
        GameInfo gameInfo = dto->getGameInfo();
        insertGameInfoIntoBuffer(buffer, gameInfo);
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error serializing game update" << std::endl;
    }
    return buffer;
}

/*
 * Inserta una posición (x, y) en el buffer en formato de red.
 */
void Serializer::insertPositionIntoBuffer(std::vector<char>& buffer, const uint32_t& x,
                                          const uint32_t& y) {
    try {
        uint32_t x_network = htonl(x);
        const auto* xp = reinterpret_cast<const unsigned char*>(&x_network);
        buffer.insert(buffer.end(), xp, xp + sizeof(uint32_t));

        uint32_t y_network = htonl(y);
        const auto* yp = reinterpret_cast<const unsigned char*>(&y_network);
        buffer.insert(buffer.end(), yp, yp + sizeof(uint32_t));
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error inserting position into buffer" << std::endl;
    }
}

/*
 * Inserta un entero en el buffer en formato de red.
 */
void Serializer::insert_int_into_buffer(std::vector<char>& buffer, const int& value) {
    try {
        uint32_t network_value = htonl(value);
        const auto* p = reinterpret_cast<const unsigned char*>(&network_value);
        buffer.insert(buffer.end(), p, p + sizeof(uint32_t));
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error inserting int into buffer" << std::endl;
    }
}

/*
 * Serializa un DTO de jugador en un buffer.
 */
std::vector<char> Serializer::serializePlayerDTO(const std::unique_ptr<PlayerDTO>& dto) {
    std::vector<char> buffer;
    try {
        buffer.push_back(static_cast<char>(dto->getPlayerId()));
        buffer.push_back(static_cast<char>(dto->getDamage()));
        buffer.push_back(static_cast<char>(dto->getHealth()));
        buffer.push_back(static_cast<char>(dto->getSpeed()));
        buffer.push_back(static_cast<char>(dto->getRespawnTime()));
        insertPositionIntoBuffer(buffer, dto->getX(), dto->getY());
        buffer.push_back(static_cast<char>(dto->getCharacterType()));
        buffer.push_back(static_cast<char>(dto->getState()));
        insert_int_into_buffer(buffer, dto->getScore());
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error serializing player" << std::endl;
    }
    return buffer;
}

/*
 * Serializa un DTO de enemigo en un buffer.
 */
std::vector<char> Serializer::serializeEnemyDTO(const std::unique_ptr<EnemyDTO>& dto) {
    std::vector<char> buffer;
    try {
        buffer.push_back(static_cast<char>(dto->getEnemyId()));
        buffer.push_back(static_cast<char>(dto->getDamage()));
        buffer.push_back(static_cast<char>(dto->getHealth()));
        buffer.push_back(static_cast<char>(dto->getSpeed()));
        insertPositionIntoBuffer(buffer, dto->getX(), dto->getY());
        buffer.push_back(static_cast<char>(dto->getEnemyType()));
        buffer.push_back(static_cast<char>(dto->getState()));
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error serializing enemy" << std::endl;
    }
    return buffer;
}

/*
 * Serializa un DTO de bala en un buffer.
 */
std::vector<char> Serializer::serializeBulletDTO(const std::unique_ptr<BulletDTO>& dto) {
    std::vector<char> buffer;
    try {
        buffer.push_back(static_cast<char>(dto->getBulletId()));
        insert_int_into_buffer(buffer, dto->getDamage());
        insert_int_into_buffer(buffer, dto->getSpeed());
        insertPositionIntoBuffer(buffer, dto->getX(), dto->getY());
        insert_int_into_buffer(buffer, dto->getShooterId());
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error serializing bullet" << std::endl;
    }
    return buffer;
}

/*
 * Serializa un DTO de ítem en un buffer.
 */
std::vector<char> Serializer::serializeItemDTO(const std::unique_ptr<ItemDTO>& dto) {
    std::vector<char> buffer;
    try {
        insertPositionIntoBuffer(buffer, dto->getX(), dto->getY());
        buffer.push_back(static_cast<char>(dto->getItemType()));
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error serializing item" << std::endl;
    }
    return buffer;
}

/*
 * Serializa un DTO de tile en un buffer.
 */
std::vector<char> Serializer::serializeTileDTO(const std::unique_ptr<TileDTO>& dto) {
    std::vector<char> buffer;
    try {
        insertPositionIntoBuffer(buffer, dto->getX(), dto->getY());
        ObstacleType type = dto->getObstacleType();
        buffer.push_back(static_cast<char>(type));
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error serializing tile" << std::endl;
    }
    return buffer;
}

/*
 * Serializa un DTO de arma en un buffer.
 */
std::vector<char> Serializer::serializeWeaponDTO(const std::unique_ptr<WeaponDTO>& dto) {
    std::vector<char> buffer;
    try {
        buffer.push_back(static_cast<char>(dto->getWeaponId()));
        insert_int_into_buffer(buffer, dto->getDamage());
        insert_int_into_buffer(buffer, dto->getAmmo());
        insert_int_into_buffer(buffer, dto->getShootSpeed());
        insertPositionIntoBuffer(buffer, dto->getX(), dto->getY());
        std::vector<char> bullet = serializeBulletDTO(dto->getBullet());
        buffer.insert(buffer.end(), bullet.begin(), bullet.end());
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error serializing weapon" << std::endl;
    }
    return buffer;
}

/*
 * Envía un DTO del juego a través del protocolo.
 * Serializa y envía todos los componentes del estado del juego (jugadores, enemigos, balas, ítems, armas, tiles).
 */
void Serializer::sendGameDTO(const std::unique_ptr<GameDTO>& dto) {
    try {
        char gamedto = static_cast<char>(DTOType::GAME_DTO);
        protocol->sendDTOType(gamedto);

        std::vector<char> buffer;

        std::vector<PlayerDTO> players = dto->getPlayers();
        insert_int_into_buffer(buffer, static_cast<int>(players.size()));
        for (const auto& player: players) {
            std::vector<char> playerBuffer =
                    serializePlayerDTO(std::make_unique<PlayerDTO>(player));
            buffer.insert(buffer.end(), playerBuffer.begin(), playerBuffer.end());
        }

        std::vector<EnemyDTO> enemies = dto->getEnemies();
        insert_int_into_buffer(buffer, static_cast<int>(enemies.size()));
        for (const auto& enemy: enemies) {
            std::vector<char> enemyBuffer = serializeEnemyDTO(std::make_unique<EnemyDTO>(enemy));
            buffer.insert(buffer.end(), enemyBuffer.begin(), enemyBuffer.end());
        }

        std::vector<BulletDTO> bullets = dto->getBullets();
        insert_int_into_buffer(buffer, static_cast<int>(bullets.size()));
        for (const auto& bullet: bullets) {
            std::vector<char> bulletBuffer =
                    serializeBulletDTO(std::make_unique<BulletDTO>(bullet));
            buffer.insert(buffer.end(), bulletBuffer.begin(), bulletBuffer.end());
        }

        std::vector<ItemDTO> items = dto->getItems();
        insert_int_into_buffer(buffer, static_cast<int>(items.size()));
        for (const auto& item: items) {
            std::vector<char> itemBuffer = serializeItemDTO(std::make_unique<ItemDTO>(item));
            buffer.insert(buffer.end(), itemBuffer.begin(), itemBuffer.end());
        }

        std::vector<WeaponDTO> weapons = dto->getWeapons();
        insert_int_into_buffer(buffer, static_cast<int>(weapons.size()));
        for (const auto& weapon: weapons) {
            std::vector<char> weaponBuffer =
                    serializeWeaponDTO(std::make_unique<WeaponDTO>(weapon));
            buffer.insert(buffer.end(), weaponBuffer.begin(), weaponBuffer.end());
        }

        std::vector<TileDTO> tiles = dto->getTiles();
        insert_int_into_buffer(buffer, static_cast<int>(tiles.size()));
        for (const auto& tile: tiles) {
            std::vector<char> tileBuffer = serializeTileDTO(std::make_unique<TileDTO>(tile));
            buffer.insert(buffer.end(), tileBuffer.begin(), tileBuffer.end());
        }

        protocol->sendData(buffer);
    } catch (const std::exception& e) {
        std::cerr << "[SERVER SERIALIZER] Error sending gameDTO" << std::endl;
    }
}
