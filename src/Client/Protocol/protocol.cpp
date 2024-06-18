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

// Receive PlayerId
void ClientProtocol::receivePlayerId(uint8_t& playerId) {
    socket->recvall(&playerId, sizeof(uint8_t), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        this->close();
    }
}

// Receive DTO Type
void ClientProtocol::receiveDTOType(char& dtoType) {
    socket->recvall(&dtoType, sizeof(char), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        this->close();
    }
}

void ClientProtocol::receiveCommandDTO(std::unique_ptr<DTO>& dto) {
    try {
        char lobbyTypeChar;
        socket->recvall(&lobbyTypeChar, sizeof(char), &closed);
        std::cout << "[RECEIVER] Received command: " << static_cast<int>(lobbyTypeChar)
                  << std::endl;
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            std::cout << "[RECEIVER] Connection closed, exiting receiveCommandDTO" << std::endl;
            return;
        }
        switch (static_cast<Command>(lobbyTypeChar)) {
            case Command::START_GAME:
                dto = std::make_unique<StartGameDTO>();
                break;
            case Command::CREATE_GAME:
                uint8_t gameId;
                this->socket->recvall(&gameId, sizeof(uint8_t), &closed);
                this->was_closed.store(closed);
                if (this->was_closed.load()) {
                    return;
                }
                dto = std::make_unique<CreateGameDTO>(gameId);
                break;
            case Command::GAMES_LIST:
                this->receiveGamesList(dto);
                break;
            case Command::MAPS_LIST:
                this->receiveMapsList(dto);
                break;
            case Command::GAME_UPDATE:
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
    this->socket->recvall(&gameId, sizeof(uint8_t), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        return {};
    }
    uint8_t nameLength;
    this->socket->recvall(&nameLength, sizeof(uint8_t), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        std::cout << "[CLIENT RECEIVER] Connection closed, exiting receiveGameUpdate" << std::endl;
        return {};
    }
    std::string name;
    name.resize(nameLength);
    socket->recvall(&name[0], nameLength, &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        return {};
    }
    uint8_t maxPlayers;
    this->socket->recvall(&maxPlayers, sizeof(uint8_t), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        return {};
    }
    uint8_t currentPlayers;
    this->socket->recvall(&currentPlayers, sizeof(uint8_t), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        return {};
    }
    uint8_t mapId;
    this->socket->recvall(&mapId, sizeof(uint8_t), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        return {};
    }
    uint8_t mapNameLength;
    this->socket->recvall(&mapNameLength, sizeof(uint8_t), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        return {};
    }
    std::string mapName;
    mapName.resize(mapNameLength);
    socket->recvall(&mapName[0], mapNameLength, &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        return {};
    }
    GameInfo gi(gameId, name, maxPlayers, currentPlayers, mapId);
    return std::move(gi);
}

void ClientProtocol::receiveGamesList(std::unique_ptr<DTO>& dto) {
    try {
        uint8_t gamesAmount;
        socket->recvall(&gamesAmount, sizeof(uint8_t), &closed);
        std::cout << "[Client Receiver | Receive Games List] Received games amount: " << static_cast<int>(gamesAmount) << std::endl;
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            return;
        }
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
        socket->recvall(&mapsAmount, sizeof(uint8_t), &closed);
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            return;
        }
        std::unordered_map<uint8_t, std::string> mapsMap;
        for (int i = 0; i < mapsAmount; i++) {
            uint8_t mapId;
            socket->recvall(&mapId, sizeof(uint8_t), &closed);
            this->was_closed.store(closed);
            if (this->was_closed.load()) {
                return;
            }
            uint8_t nameLength;
            socket->recvall(&nameLength, sizeof(uint8_t), &closed);
            this->was_closed.store(closed);
            if (this->was_closed.load()) {
                return;
            }
            std::string name;
            name.resize(nameLength);
            socket->recvall(&name[0], nameLength, &closed);
            this->was_closed.store(closed);
            if (this->was_closed.load()) {
                return;
            }
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
        uint8_t cant_jugadores;
        this->socket->recvall(&cant_jugadores, sizeof(uint8_t), &closed);
        std::cout << "[CLIENT RECEIVER] Number of players: " << static_cast<int>(cant_jugadores)
                  << std::endl;

        uint8_t aux;
        for (uint8_t i = 0; i < cant_jugadores; i++) {
            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto playerId = static_cast<uint8_t>(aux);

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int damage = static_cast<int>(aux);

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int health = static_cast<int>(aux);

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int speed = static_cast<int>(aux);

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int getRespawnTime = static_cast<int>(aux);

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto x = static_cast<uint8_t>(aux);

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto y = static_cast<uint8_t>(aux);

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto pj_type = static_cast<CharacterType>(aux);

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto state = static_cast<CharacterStateEntity>(aux);

            WeaponDTO weapon(0, 0, 0, 0, 0);
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
        uint8_t cant_enemies;
        this->socket->recvall(&cant_enemies, sizeof(uint8_t), &closed);

        uint8_t aux;
        for (uint8_t i = 0; i < cant_enemies; i++) {
            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto enemyId = static_cast<uint8_t>(aux);

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int enemy_damage = static_cast<int>(aux);

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int enemy_health = static_cast<int>(aux);

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int enemy_speed = static_cast<int>(aux);
            std::cout << "[CLIENT RECEIVER ENEMY] Speed: " << enemy_speed << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto enemy_x = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER ENEMY] X: " << static_cast<int>(enemy_x) << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto enemy_y = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER ENEMY] Y: " << static_cast<int>(enemy_y) << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto enemy_type = static_cast<EnemyType>(aux);
            std::cout << "[CLIENT RECEIVER ENEMY] Type: " << static_cast<int>(enemy_type)
                      << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
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
        uint8_t cant_bullets;
        this->socket->recvall(&cant_bullets, sizeof(uint8_t), &closed);
        std::cout << "[CLIENT RECEIVER] Number of bullets: " << static_cast<int>(cant_bullets)
                  << std::endl;

        uint8_t aux;
        for (uint8_t i = 0; i < cant_bullets; i++) {
            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto bulletId = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER BULLET] Bullet ID: " << static_cast<int>(bulletId)
                      << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int bullet_damage = static_cast<int>(aux);
            std::cout << "[CLIENT RECEIVER BULLET] Damage: " << bullet_damage << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int bullet_speed = static_cast<int>(aux);
            std::cout << "[CLIENT RECEIVER BULLET] Speed: " << bullet_speed << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto bullet_x = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER BULLET] X: " << static_cast<int>(bullet_x) << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto bullet_y = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER BULLET] Y: " << static_cast<int>(bullet_y) << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int shooterId = static_cast<int>(aux);
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
        uint8_t cant_items;
        this->socket->recvall(&cant_items, sizeof(uint8_t), &closed);
        std::cout << "[CLIENT RECEIVER] Number of items: " << static_cast<int>(cant_items)
                  << std::endl;

        uint8_t aux;
        for (uint8_t i = 0; i < cant_items; i++) {
            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto item_x = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER ITEM] X: " << static_cast<int>(item_x) << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto item_y = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER ITEM] Y: " << static_cast<int>(item_y) << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
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
        uint8_t cant_weapons;
        this->socket->recvall(&cant_weapons, sizeof(uint8_t), &closed);
        std::cout << "[CLIENT RECEIVER] Number of weapons: " << static_cast<int>(cant_weapons)
                  << std::endl;

        uint8_t aux;
        for (uint8_t i = 0; i < cant_weapons; i++) {
            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto weaponId = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Weapon ID: " << static_cast<int>(weaponId)
                      << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int weapon_damage = static_cast<int>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Damage: " << weapon_damage << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int weapon_ammo = static_cast<int>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Ammo: " << weapon_ammo << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int shoot_speed = static_cast<int>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Shoot speed: " << shoot_speed << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto weapon_x = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] X: " << static_cast<int>(weapon_x) << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto weapon_y = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Y: " << static_cast<int>(weapon_y) << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto bulletId = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Bullet ID: " << static_cast<int>(bulletId)
                      << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int bullet_damage = static_cast<int>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Bullet damage: " << bullet_damage << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int bullet_speed = static_cast<int>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Bullet speed: " << bullet_speed << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto bullet_x = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Bullet X: " << static_cast<int>(bullet_x)
                      << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto bullet_y = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER WEAPON] Bullet Y: " << static_cast<int>(bullet_y)
                      << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            int shooterId = static_cast<int>(aux);
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
        uint8_t cant_tiles;
        this->socket->recvall(&cant_tiles, sizeof(uint8_t), &closed);
        std::cout << "[CLIENT RECEIVER] Number of tiles: " << static_cast<int>(cant_tiles)
                  << std::endl;

        uint8_t aux;
        for (uint8_t i = 0; i < cant_tiles; i++) {
            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto tile_x = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER TILE] X: " << static_cast<int>(tile_x) << std::endl;

            this->socket->recvall(&aux, sizeof(uint8_t), &closed);
            auto tile_y = static_cast<uint8_t>(aux);
            std::cout << "[CLIENT RECEIVER TILE] Y: " << static_cast<int>(tile_y) << std::endl;

            TileDTO tile(tile_x, tile_y);
            tiles.push_back(tile);
        }
    } catch (const std::exception& e) {
        std::cerr << "[CLIENT RECEIVER] Error in receiveTiles: " << e.what() << std::endl;
    }
    return tiles;
}

