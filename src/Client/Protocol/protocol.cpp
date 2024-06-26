#include "protocol.h"

#include "printer.h"

ClientProtocol::ClientProtocol(const std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed) :
    socket(socket), was_closed(was_closed), closed(false) {}

// State
bool ClientProtocol::isClosed() {
    return this->was_closed.load();
}

// Connection
void ClientProtocol::close() {
    if (this->isClosed()) return;
    this->closeSocket();
}

void ClientProtocol::closeSocket() {
    this->socket->shutdown(2);
    this->socket->close();
}

// Receiving types
bool ClientProtocol::receive_uint8(uint8_t& value) {
    this->socket->recvall(&value, sizeof(uint8_t), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        this->close();
        return false;
    }
    return true;
}

bool ClientProtocol::receive_uint32(uint32_t& value) {
    this->socket->recvall(&value, sizeof(uint32_t), &closed);
    value = ntohl(value);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        this->close();
        return false;
    }
    return true;
}

bool ClientProtocol::receive_char(char& value) {
    this->socket->recvall(&value, sizeof(char), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        this->close();
        return false;
    }
    return true;
}

bool ClientProtocol::receive_string(const uint8_t& length, std::string& value) {
    value.resize(length);
    this->socket->recvall(&value[0], length, &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        this->close();
        return false;
    }
    return true;
}

// Receive Player ID
void ClientProtocol::receivePlayerId(uint8_t& playerId) {
    if (!this->receive_uint8(playerId)) {
        return;
    }
}

// Receive DTO Type
void ClientProtocol::receiveDTOType(char& dtoType) {
    if (!this->receive_char(dtoType)) {
        return;
    }
}

void ClientProtocol::receiveCommandDTO(std::unique_ptr<DTO>& dto) {
    try {
        std::cout << "[RECEIVER] Receiving command DTO" << std::endl;
        char lobbyTypeChar;
        if (!this->receive_char(lobbyTypeChar)) {
            return;
        }
        switch (static_cast<Command>(lobbyTypeChar)) {
            case Command::START_GAME:
                std::cout << "[RECEIVER] Receiving START_GAME command" << std::endl;
                dto = std::make_unique<StartGameDTO>();
                break;
            case Command::CREATE_GAME:
                std::cout << "[RECEIVER] Receiving CREATE_GAME command" << std::endl;
                uint8_t gameId;
                if (!this->receive_uint8(gameId)) {
                    return;
                }
                dto = std::make_unique<CreateGameDTO>(gameId);
                break;
            case Command::JOIN_GAME:
                std::cout << "[RECEIVER] Receiving JOIN_GAME command" << std::endl;
                this->receiveJoinGame(dto);
                break;
            case Command::GAMES_LIST:
                std::cout << "[RECEIVER] Receiving GAMES_LIST command" << std::endl;
                this->receiveGamesList(dto);
                break;
            case Command::MAPS_LIST:
                std::cout << "[RECEIVER] Receiving MAPS_LIST command" << std::endl;
                this->receiveMapsList(dto);
                break;
            case Command::GAME_UPDATE:
                std::cout << "[RECEIVER] Receiving GAME_UPDATE command" << std::endl;
                this->receiveGameUpdate(dto);
                break;
            default:
                std::cout << "[RECEIVER] Unknown command received" << std::endl;
                break;
        }
    } catch (const std::exception& e) {
        std::cerr << "[RECEIVER] Error in receiveCommandDTO: " << e.what() << std::endl;
    }
}

GameInfo ClientProtocol::receiveGameInfo() {
    uint8_t gameId;
    if (!this->receive_uint8(gameId)) return {};
    uint8_t nameLength;
    if (!this->receive_uint8(nameLength)) return {};
    std::string name;
    if (!this->receive_string(nameLength, name)) return {};
    uint8_t maxPlayers;
    if(!this->receive_uint8(maxPlayers)) return {};
    uint8_t currentPlayers;
    if(!this->receive_uint8(currentPlayers)) return {};
    uint8_t mapId;
    if(!this->receive_uint8(mapId)) return {};
    uint8_t mapNameLength;
    if(!this->receive_uint8(mapNameLength)) return {};
    std::string mapName;
    if(!this->receive_string(mapNameLength, mapName)) return {};
    GameInfo gi(gameId, name, maxPlayers, currentPlayers, mapId);
    return std::move(gi);
}

void ClientProtocol::receiveGamesList(std::unique_ptr<DTO>& dto) {
    try {
        uint8_t gamesAmount;
        if (!this->receive_uint8(gamesAmount)) return;
        std::unordered_map<uint8_t, GameInfo> gamesMap;
        for (int i = 0; i < gamesAmount; i++) {
            GameInfo gameInfo = this->receiveGameInfo();
            gamesMap[gameInfo.getGameId()] = gameInfo;
        }
        dto = std::make_unique<GamesListDTO>(gamesMap);
    } catch (const std::exception& e) {
        std::cerr << "[CLIENT RECEIVER] Error in receiveGamesList: " << e.what() << std::endl;
    }
}

void ClientProtocol::receiveMapsList(std::unique_ptr<DTO>& dto) {
    try {
        uint8_t mapsAmount;
        if (!this->receive_uint8(mapsAmount)) return;
        std::unordered_map<uint8_t, std::string> mapsMap;
        for (int i = 0; i < mapsAmount; i++) {
            uint8_t mapId;
            if (!this->receive_uint8(mapId)) return;
            uint8_t nameLength;
            if (!this->receive_uint8(nameLength)) return;
            std::string name;
            if (!this->receive_string(nameLength, name)) return;
            mapsMap[mapId] = name;
        }
        dto = std::make_unique<MapsListDTO>(mapsMap);
    } catch (const std::exception& e) {
        std::cerr << "[CLIENT RECEIVER] Error in receiveMapsList: " << e.what() << std::endl;
    }
}

void ClientProtocol::receiveGameUpdate(std::unique_ptr<DTO>& dto) {
    GameInfo gi = this->receiveGameInfo();
    dto = std::make_unique<GameUpdateDTO>(gi);
}

void ClientProtocol::receiveJoinGame(std::unique_ptr<DTO>& dto) {
    uint8_t gameId;
    if (!this->receive_uint8(gameId)) return;
    uint8_t currentPlayers;
    if (!this->receive_uint8(currentPlayers)) return;
    dto = std::make_unique<JoinGameDTO>(gameId, currentPlayers);
}

void ClientProtocol::receiveGameDTO(std::unique_ptr<DTO>& dto) {
    try {
        std::vector<PlayerDTO> players = receivePlayers();
        std::vector<EnemyDTO> enemies = receiveEnemies();
        std::vector<BulletDTO> bullets = receiveBullets();
        std::vector<ItemDTO> items = receiveItems();
        std::vector<WeaponDTO> weapons = receiveWeapons();
        std::vector<TileDTO> tiles = receiveTiles();

        dto = std::make_unique<GameDTO>(players, enemies, bullets, items, weapons, tiles);
    } catch (const std::exception& e) {
        std::cerr << "[CLIENT RECEIVER] Error in receiveGameDTO: " << e.what() << std::endl;
    }
}

std::vector<PlayerDTO> ClientProtocol::receivePlayers() {
    std::vector<PlayerDTO> players;
    try {
        uint32_t cant_jugadores;
        if (!this->receive_uint32(cant_jugadores)) return {};
        uint8_t aux;
        uint32_t aux32;
        for (uint32_t i = 0; i < cant_jugadores; i++) {
            if (!this->receive_uint8(aux)) return {};
            auto playerId = static_cast<uint8_t>(aux);

            if (!this->receive_uint8(aux)) return {};
            auto damage = static_cast<uint8_t>(aux);

            if (!this->receive_uint8(aux)) return {};
            auto health = static_cast<uint8_t>(aux);

            if (!this->receive_uint8(aux)) return {};
            auto speed = static_cast<uint8_t>(aux);

            if (!this->receive_uint8(aux)) return {};
            auto getRespawnTime = static_cast<uint8_t>(aux);

            if (!this->receive_uint32(aux32)) return {};
            uint32_t x = aux32;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t y = aux32;

            Printer::printDebugHighlightedMessage("Player id: " + std::to_string(playerId)+ " x: " + std::to_string(x) + " y: " + std::to_string(y));

            if (!this->receive_uint8(aux)) return {};
            auto pj_type = static_cast<CharacterType>(aux);

            if (!this->receive_uint8(aux)) return {};
            auto state = static_cast<CharacterStateEntity>(aux);

            if (!this->receive_uint32(aux32)) return {};
            uint32_t score = aux32;      

            PlayerDTO player(x, y, playerId, health, damage, speed, pj_type, state, score);
            players.push_back(player);
        }
    } catch (const std::exception& e) {
        std::cerr << "[CLIENT RECEIVER] Error in receivePlayers: " << e.what() << std::endl;
    }
    return players;
}

std::vector<EnemyDTO> ClientProtocol::receiveEnemies() {
    std::vector<EnemyDTO> enemies;
    try {
        uint32_t cant_enemies;
        if (!this->receive_uint32(cant_enemies)) return {};

        uint8_t aux;
        uint32_t aux32;
        for (uint32_t i = 0; i < cant_enemies; i++) {
            if (!this->receive_uint8(aux)) return {};
            auto enemyId = static_cast<uint8_t>(aux);

            if (!this->receive_uint8(aux)) return {};
            auto enemy_damage = static_cast<uint8_t>(aux);

            if (!this->receive_uint8(aux)) return {};
            auto enemy_health = static_cast<uint8_t>(aux);

            if (!this->receive_uint8(aux)) return {};
            auto enemy_speed = static_cast<uint8_t>(aux);

            if (!this->receive_uint32(aux32)) return {};
            uint32_t enemy_x = aux32;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t enemy_y = aux32;

            if (!this->receive_uint8(aux)) return {};
            auto enemy_type = static_cast<EnemyType>(aux);

            if (!this->receive_uint8(aux)) return {};
            auto enemy_state = static_cast<EnemyStateEntity>(aux);

            EnemyDTO enemy(enemy_x, enemy_y, enemyId, enemy_health, enemy_damage, enemy_speed,
                           enemy_type, enemy_state);
            enemies.push_back(enemy);
        }
    } catch (const std::exception& e) {
        std::cerr << "[CLIENT RECEIVER] Error in receiveEnemies: " << e.what() << std::endl;
    }
    return enemies;
}

std::vector<BulletDTO> ClientProtocol::receiveBullets() {
    std::vector<BulletDTO> bullets;
    try {
        uint32_t cant_bullets;
        if (!this->receive_uint32(cant_bullets)) return {};

        uint8_t aux;
        uint32_t aux32;
        for (uint32_t i = 0; i < cant_bullets; i++) {
            if (!this->receive_uint8(aux)) return {};
            auto bulletId = static_cast<uint8_t>(aux);

            if (!this->receive_uint32(aux32)) return {};
            int bullet_damage = static_cast<int>(aux32);

            if (!this->receive_uint32(aux32)) return {};
            int bullet_speed = static_cast<int>(aux32);

            if (!this->receive_uint32(aux32)) return {};
            uint32_t bullet_x = aux32;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t bullet_y = aux32;

            if (!this->receive_uint32(aux32)) return {};
            int shooterId = static_cast<int>(aux32);

            BulletDTO bullet(bullet_x, bullet_y, bulletId, bullet_damage, bullet_speed, shooterId);
            bullets.push_back(bullet);
        }
    } catch (const std::exception& e) {
        std::cerr << "[CLIENT RECEIVER] Error in receiveBullets: " << e.what() << std::endl;
    }
    return bullets;
}

std::vector<ItemDTO> ClientProtocol::receiveItems() {
    std::vector<ItemDTO> items;
    try {
        uint32_t cant_items;
        if (!this->receive_uint32(cant_items)) return {};

        uint8_t aux;
        uint32_t aux32;
        for (uint32_t i = 0; i < cant_items; i++) {
            if (!this->receive_uint32(aux32)) return {};
            uint32_t item_x = aux32;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t item_y = aux32;

            if (!this->receive_uint8(aux)) return {};
            auto item_type = static_cast<ItemType>(aux);

            ItemDTO item(item_x, item_y, item_type);
            items.push_back(item);
        }
    } catch (const std::exception& e) {
        std::cerr << "[CLIENT RECEIVER] Error in receiveItems: " << e.what() << std::endl;
    }
    return items;
}

std::vector<WeaponDTO> ClientProtocol::receiveWeapons() {
    std::vector<WeaponDTO> weapons;
    try {
        uint32_t cant_weapons;
        if (!this->receive_uint32(cant_weapons)) return {};

        uint8_t aux;
        uint32_t aux32;
        for (uint32_t i = 0; i < cant_weapons; i++) {
            if (!this->receive_uint8(aux)) return {};
            auto weaponId = static_cast<uint8_t>(aux);

            if (!this->receive_uint32(aux32)) return {};
            int weapon_damage = static_cast<int>(aux32);

            if (!this->receive_uint32(aux32)) return {};
            int weapon_ammo = static_cast<int>(aux32);

            if (!this->receive_uint32(aux32)) return {};
            int shoot_speed = static_cast<int>(aux32);

            if (!this->receive_uint32(aux32)) return {};
            uint32_t weapon_x = aux32;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t weapon_y = aux32;

            if (!this->receive_uint8(aux)) return {};
            auto bulletId = static_cast<uint8_t>(aux);

            if (!this->receive_uint32(aux32)) return {};
            int bullet_damage = static_cast<int>(aux32);

            if (!this->receive_uint32(aux32)) return {};
            int bullet_speed = static_cast<int>(aux32);

            if (!this->receive_uint8(aux)) return {};
            auto bullet_x = static_cast<uint8_t>(aux);

            if (!this->receive_uint8(aux)) return {};
            auto bullet_y = static_cast<uint8_t>(aux);

            if (!this->receive_uint32(aux32)) return {};
            int shooterId = static_cast<int>(aux32);

            WeaponDTO weapon(weaponId, weapon_x, weapon_y, weapon_damage, weapon_ammo);
            weapons.push_back(weapon);
        }
    } catch (const std::exception& e) {
        std::cerr << "[CLIENT RECEIVER] Error in receiveWeapons: " << e.what() << std::endl;
    }
    return weapons;
}

std::vector<TileDTO> ClientProtocol::receiveTiles() {
    std::vector<TileDTO> tiles;
    try {
        uint32_t cant_tiles;
        if (!this->receive_uint32(cant_tiles)) return {};

        uint32_t aux32;
        uint8_t aux8;  // Cambia esto para recibir el tipo de ObstacleType
        for (uint32_t i = 0; i < cant_tiles; i++) {
            if (!this->receive_uint32(aux32)) return {};
            uint32_t tile_x = aux32;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t tile_y = aux32;

            if (!this->receive_uint8(aux8)) return {}; // Recibe el tipo de tile como uint8_t
            auto tile_type = static_cast<ObstacleType>(aux8);

            TileDTO tile(tile_x, tile_y, tile_type);
            tiles.push_back(tile);
        }
    } catch (const std::exception& e) {
        std::cerr << "[CLIENT RECEIVER] Error in receiveTiles: " << e.what() << std::endl;
    }
    return tiles;
}



