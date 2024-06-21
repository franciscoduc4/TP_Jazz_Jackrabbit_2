#include "protocol.h"

ClientProtocol::ClientProtocol(std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed) :
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
            uint8_t damage = static_cast<uint8_t>(aux);

            if (!this->receive_uint8(aux)) return {};
            uint8_t health = static_cast<uint8_t>(aux);

            if (!this->receive_uint8(aux)) return {};
            uint8_t speed = static_cast<uint8_t>(aux);

            if (!this->receive_uint8(aux)) return {};
            uint8_t getRespawnTime = static_cast<uint8_t>(aux);

            if (!this->receive_uint32(aux32)) return {};
            uint32_t x = aux32;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t y = aux32;

            if (!this->receive_uint8(aux)) return {};
            auto pj_type = static_cast<CharacterType>(aux);

            if (!this->receive_uint8(aux)) return {};
            auto state = static_cast<CharacterStateEntity>(aux);

            PlayerDTO player(x, y, playerId, health, damage, speed, pj_type, state);
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
            uint8_t enemy_damage = static_cast<uint8_t>(aux);

            if (!this->receive_uint8(aux)) return {};
            uint8_t enemy_health = static_cast<uint8_t>(aux);

            if (!this->receive_uint8(aux)) return {};
            uint8_t enemy_speed = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER ENEMY] Speed: " << enemy_speed << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t enemy_x = aux32;
            std::cout << "[CLIENT RECEIVER ENEMY] X: " << static_cast<int>(enemy_x) << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t enemy_y = aux32;
            std::cout << "[CLIENT RECEIVER ENEMY] Y: " << static_cast<int>(enemy_y) << std::endl;

            if (!this->receive_uint8(aux)) return {};
            auto enemy_type = static_cast<EnemyType>(aux);
            std::cout << "[CLIENT RECEIVER ENEMY] Type: " << static_cast<int>(enemy_type)
                      << std::endl;

            if (!this->receive_uint8(aux)) return {};
            auto enemy_state = static_cast<EnemyStateEntity>(aux);
            std::cout << "[CLIENT RECEIVER ENEMY] State: " << static_cast<int>(enemy_state)
                      << std::endl;

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
        std::cout << "[CLIENT RECEIVER] Number of bullets: " << static_cast<int>(cant_bullets)
                  << std::endl;

        uint8_t aux;
        uint32_t aux32;
        for (uint32_t i = 0; i < cant_bullets; i++) {
            if (!this->receive_uint8(aux)) return {};
            auto bulletId = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER BULLET] Bullet ID: " << static_cast<int>(bulletId)
                      << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            int bullet_damage = static_cast<int>(aux32);
            std::cout << "[CLIENT RECEIVER BULLET] Damage: " << bullet_damage << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            int bullet_speed = static_cast<int>(aux32);
            std::cout << "[CLIENT RECEIVER BULLET] Speed: " << bullet_speed << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t bullet_x = aux32;
            std::cout << "[CLIENT RECEIVER BULLET] X: " << static_cast<int>(bullet_x) << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t bullet_y = aux32;
            std::cout << "[CLIENT RECEIVER BULLET] Y: " << static_cast<int>(bullet_y) << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            int shooterId = static_cast<int>(aux32);
            std::cout << "[CLIENT RECEIVER BULLET] Shooter ID: " << shooterId << std::endl;

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
        std::cout << "[CLIENT RECEIVER] Number of items: " << static_cast<int>(cant_items)
                  << std::endl;

        uint8_t aux;
        uint32_t aux32;
        for (uint32_t i = 0; i < cant_items; i++) {
            if (!this->receive_uint32(aux32)) return {};
            uint32_t item_x = aux32;
            std::cout << "[CLIENT RECEIVER ITEM] X: " << static_cast<int>(item_x) << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t item_y = aux32;
            std::cout << "[CLIENT RECEIVER ITEM] Y: " << static_cast<int>(item_y) << std::endl;

            if (!this->receive_uint8(aux)) return {};
            auto item_type = static_cast<ItemType>(aux);
            std::cout << "[CLIENT RECEIVER ITEM] Type: " << static_cast<int>(item_type)
                      << std::endl;

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
        std::cout << "[CLIENT RECEIVER] Number of weapons: " << static_cast<int>(cant_weapons)
                  << std::endl;

        uint8_t aux;
        uint32_t aux32;
        for (uint32_t i = 0; i < cant_weapons; i++) {
            if (!this->receive_uint8(aux)) return {};
            auto weaponId = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Weapon ID: " << static_cast<int>(weaponId)
                      << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            int weapon_damage = static_cast<int>(aux32);
            std::cout << "[CLIENT RECEIVER WEAPON] Damage: " << weapon_damage << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            int weapon_ammo = static_cast<int>(aux32);
            std::cout << "[CLIENT RECEIVER WEAPON] Ammo: " << weapon_ammo << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            int shoot_speed = static_cast<int>(aux32);
            std::cout << "[CLIENT RECEIVER WEAPON] Shoot speed: " << shoot_speed << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t weapon_x = aux32;
            std::cout << "[CLIENT RECEIVER WEAPON] X: " << static_cast<int>(weapon_x) << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t weapon_y = aux32;
            std::cout << "[CLIENT RECEIVER WEAPON] Y: " << static_cast<int>(weapon_y) << std::endl;

            if (!this->receive_uint8(aux)) return {};
            auto bulletId = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Bullet ID: " << static_cast<int>(bulletId)
                      << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            int bullet_damage = static_cast<int>(aux32);
            std::cout << "[CLIENT RECEIVER WEAPON] Bullet damage: " << bullet_damage << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            int bullet_speed = static_cast<int>(aux32);
            std::cout << "[CLIENT RECEIVER WEAPON] Bullet speed: " << bullet_speed << std::endl;

            if (!this->receive_uint8(aux)) return {};
            auto bullet_x = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Bullet X: " << static_cast<int>(bullet_x)
                      << std::endl;

            if (!this->receive_uint8(aux)) return {};
            auto bullet_y = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Bullet Y: " << static_cast<int>(bullet_y)
                      << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            int shooterId = static_cast<int>(aux32);
            std::cout << "[CLIENT RECEIVER WEAPON] Shooter ID: " << shooterId << std::endl;

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
        std::cout << "[CLIENT RECEIVER] Number of tiles: " << static_cast<int>(cant_tiles) << std::endl;

        uint32_t aux32;
        uint8_t aux8;  // Cambia esto para recibir el tipo de ObstacleType
        for (uint32_t i = 0; i < cant_tiles; i++) {
            if (!this->receive_uint32(aux32)) return {};
            uint32_t tile_x = aux32;
            std::cout << "[CLIENT RECEIVER TILE] X: " << static_cast<int>(tile_x) << std::endl;

            if (!this->receive_uint32(aux32)) return {};
            uint32_t tile_y = aux32;
            std::cout << "[CLIENT RECEIVER TILE] Y: " << static_cast<int>(tile_y) << std::endl;

            if (!this->receive_uint8(aux8)) return {}; // Recibe el tipo de tile como uint8_t
            ObstacleType tile_type = static_cast<ObstacleType>(aux8);
            std::cout << "[CLIENT RECEIVER TILE] Type: " << static_cast<int>(tile_type) << std::endl;

            TileDTO tile(tile_x, tile_y, tile_type);
            tiles.push_back(tile);
        }
    } catch (const std::exception& e) {
        std::cerr << "[CLIENT RECEIVER] Error in receiveTiles: " << e.what() << std::endl;
    }
    return tiles;
}



