#include "receiverThread.h"

#include <netinet/in.h>

#include "../../Common/Types/command.h"
#include "../../Common/Types/entity.h"
#include "DTO/createGame.h"
#include "DTO/startGame.h"

ReceiverThread::ReceiverThread(Deserializer& deserializer, std::shared_ptr<Socket>& socket,
                               std::atomic<bool>& was_closed):
        deserializer(deserializer), socket(socket), was_closed(was_closed), closed(false) {
    std::cout << "[RECEIVER] ReceiverThread initialized" << std::endl;
}

void ReceiverThread::receiveCommandDTO() {
    char lobbyTypeChar;
    socket->recvall(&lobbyTypeChar, sizeof(char), &closed);
    std::cout << "[RECEIVER] Received command: " << static_cast<int>(lobbyTypeChar) << std::endl;
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        std::cout << "[RECEIVER] Connection closed, exiting receiveCommandDTO" << std::endl;
        return;
    }
    if (lobbyTypeChar == static_cast<char>(Command::START_GAME)) {
        std::unique_ptr<DTO> dto = std::make_unique<StartGameDTO>(0);
        this->deserializer.deserialize_lobbyMsg(dto);
        std::cout << "[RECEIVER] START_GAME command deserialized" << std::endl;
    } else if (lobbyTypeChar == static_cast<char>(Command::CREATE_GAME)) {
        uint8_t gameId;
        this->socket->recvall(&gameId, sizeof(uint8_t), &closed);
        gameId = ntohl(gameId);
        std::cout << "[RECEIVER] Received game id: " << static_cast<int>(gameId) << std::endl;
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            std::cout << "[RECEIVER] Connection closed, exiting receiveCommandDTO" << std::endl;
            return;
        }
        std::unique_ptr<DTO> cgDto = std::make_unique<CreateGameDTO>(gameId);
        this->deserializer.deserialize_lobbyMsg(cgDto);
        std::cout << "[RECEIVER] CREATE_GAME command deserialized" << std::endl;
    }

    auto lobbyState = static_cast<LobbyState>(lobbyTypeChar);
    if (lobbyState == LobbyState::GAMES_LIST) {
        this->receiveGamesList();
    }
}

std::vector<PlayerDTO> ReceiverThread::receivePlayers() {
    std::vector<PlayerDTO> players;
    uint8_t cant_jugadores;

    this->socket->recvall(&cant_jugadores, sizeof(uint8_t), &closed);
    std::cout << "[CLIENT RECEIVER] Number of players: " << static_cast<int>(cant_jugadores)
              << std::endl;

    uint8_t aux;
    for (uint8_t i = 0; i < cant_jugadores; i++) {
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint8_t playerId = static_cast<uint8_t>(aux);
        std::cout << "[CLIENT RECEIVER PLAYER] Player ID: " << static_cast<int>(playerId)
                  << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int damage = static_cast<int>(aux);
        std::cout << "[CLIENT RECEIVER PLAYER] Damage: " << damage << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int health = static_cast<int>(aux);
        std::cout << "[CLIENT RECEIVER PLAYER] Health: " << health << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int speed = static_cast<int>(aux);
        std::cout << "[CLIENT RECEIVER PLAYER] Speed: " << speed << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int getRespawnTime = static_cast<int>(aux);
        std::cout << "[CLIENT RECEIVER PLAYER] Respawn time: " << getRespawnTime << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t x = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER PLAYER] X: " << x << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t y = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER PLAYER] Y: " << y << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        CharacterType pj_type = static_cast<CharacterType>(aux);
        std::cout << "[CLIENT RECEIVER PLAYER] Character type: " << static_cast<int>(pj_type)
                  << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        CharacterStateEntity state = static_cast<CharacterStateEntity>(aux);
        std::cout << "[CLIENT RECEIVER PLAYER] Character state: " << static_cast<int>(state)
                  << std::endl;

        WeaponDTO weapon(0, 0, 0, 0, 0);  // Placeholder weapon
        PlayerDTO player(x, y, playerId, health, damage, speed, pj_type, state);
        players.push_back(player);
    }

    return players;
}

std::vector<EnemyDTO> ReceiverThread::receiveEnemies() {
    std::vector<EnemyDTO> enemies;
    uint8_t cant_enemies;

    this->socket->recvall(&cant_enemies, sizeof(uint8_t), &closed);
    std::cout << "[CLIENT RECEIVER] Number of enemies: " << static_cast<int>(cant_enemies)
              << std::endl;

    uint8_t aux;
    for (uint8_t i = 0; i < cant_enemies; i++) {
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint8_t enemyId = static_cast<uint8_t>(aux);
        std::cout << "[CLIENT RECEIVER ENEMY] Enemy ID: " << static_cast<int>(enemyId) << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int enemy_damage = static_cast<int>(aux);
        std::cout << "[CLIENT RECEIVER ENEMY] Damage: " << enemy_damage << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int enemy_health = static_cast<int>(aux);
        std::cout << "[CLIENT RECEIVER ENEMY] Health: " << enemy_health << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int enemy_speed = static_cast<int>(aux);
        std::cout << "[CLIENT RECEIVER ENEMY] Speed: " << enemy_speed << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t enemy_x = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER ENEMY] X: " << enemy_x << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t enemy_y = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER ENEMY] Y: " << enemy_y << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        EnemyType enemy_type = static_cast<EnemyType>(aux);
        std::cout << "[CLIENT RECEIVER ENEMY] Type: " << static_cast<int>(enemy_type) << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        EnemyStateEntity enemy_state = static_cast<EnemyStateEntity>(aux);
        std::cout << "[CLIENT RECEIVER ENEMY] State: " << static_cast<int>(enemy_state)
                  << std::endl;

        EnemyDTO enemy(enemy_x, enemy_y, enemyId, enemy_health, enemy_damage, enemy_speed,
                       enemy_type, enemy_state);
        enemies.push_back(enemy);
    }

    return enemies;
}

std::vector<BulletDTO> ReceiverThread::receiveBullets() {
    std::vector<BulletDTO> bullets;
    uint8_t cant_bullets;

    this->socket->recvall(&cant_bullets, sizeof(uint8_t), &closed);
    std::cout << "[CLIENT RECEIVER] Number of bullets: " << static_cast<int>(cant_bullets)
              << std::endl;

    uint8_t aux;
    for (uint8_t i = 0; i < cant_bullets; i++) {
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint8_t bulletId = static_cast<uint8_t>(aux);
        std::cout << "[CLIENT RECEIVER BULLET] Bullet ID: " << static_cast<int>(bulletId)
                  << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int bullet_damage = static_cast<int>(aux);
        std::cout << "[CLIENT RECEIVER BULLET] Damage: " << bullet_damage << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int bullet_speed = static_cast<int>(aux);
        std::cout << "[CLIENT RECEIVER BULLET] Speed: " << bullet_speed << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t bullet_x = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER BULLET] X: " << bullet_x << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t bullet_y = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER BULLET] Y: " << bullet_y << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int shooterId = static_cast<int>(aux);
        std::cout << "[CLIENT RECEIVER BULLET] Shooter ID: " << shooterId << std::endl;

        BulletDTO bullet(bullet_x, bullet_y, bulletId, bullet_damage, bullet_speed, shooterId);
        bullets.push_back(bullet);
    }

    return bullets;
}

std::vector<ItemDTO> ReceiverThread::receiveItems() {
    std::vector<ItemDTO> items;
    uint8_t cant_items;

    this->socket->recvall(&cant_items, sizeof(uint8_t), &closed);
    std::cout << "[CLIENT RECEIVER] Number of items: " << static_cast<int>(cant_items) << std::endl;

    uint8_t aux;
    for (uint8_t i = 0; i < cant_items; i++) {
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t item_x = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER ITEM] X: " << item_x << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t item_y = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER ITEM] Y: " << item_y << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        ItemType item_type = static_cast<ItemType>(aux);
        std::cout << "[CLIENT RECEIVER ITEM] Type: " << static_cast<int>(item_type) << std::endl;

        ItemDTO item(item_x, item_y, item_type);
        items.push_back(item);
    }

    return items;
}

std::vector<WeaponDTO> ReceiverThread::receiveWeapons() {
    std::vector<WeaponDTO> weapons;
    uint8_t cant_weapons;

    this->socket->recvall(&cant_weapons, sizeof(uint8_t), &closed);
    std::cout << "[CLIENT RECEIVER] Number of weapons: " << static_cast<int>(cant_weapons)
              << std::endl;

    uint8_t aux;
    for (uint8_t i = 0; i < cant_weapons; i++) {
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint8_t weaponId = static_cast<uint8_t>(aux);
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
        uint16_t weapon_x = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER WEAPON] X: " << weapon_x << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t weapon_y = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER WEAPON] Y: " << weapon_y << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint8_t bulletId = static_cast<uint8_t>(aux);
        std::cout << "[CLIENT RECEIVER WEAPON] Bullet ID: " << static_cast<int>(bulletId)
                  << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int bullet_damage = static_cast<int>(aux);
        std::cout << "[CLIENT RECEIVER WEAPON] Bullet damage: " << bullet_damage << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int bullet_speed = static_cast<int>(aux);
        std::cout << "[CLIENT RECEIVER WEAPON] Bullet speed: " << bullet_speed << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t bullet_x = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER WEAPON] Bullet X: " << bullet_x << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t bullet_y = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER WEAPON] Bullet Y: " << bullet_y << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int shooterId = static_cast<int>(aux);
        std::cout << "[CLIENT RECEIVER WEAPON] Shooter ID: " << shooterId << std::endl;

        WeaponDTO weapon(weaponId, weapon_x, weapon_y, weapon_damage, weapon_ammo);
        weapons.push_back(weapon);
    }

    return weapons;
}

std::vector<TileDTO> ReceiverThread::receiveTiles() {
    std::vector<TileDTO> tiles;
    uint8_t cant_tiles;

    this->socket->recvall(&cant_tiles, sizeof(uint8_t), &closed);
    std::cout << "[CLIENT RECEIVER] Number of tiles: " << static_cast<int>(cant_tiles) << std::endl;

    uint8_t aux;
    for (uint8_t i = 0; i < cant_tiles; i++) {
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t tile_x = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER TILE] X: " << tile_x << std::endl;

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t tile_y = static_cast<uint16_t>(aux);
        std::cout << "[CLIENT RECEIVER TILE] Y: " << tile_y << std::endl;

        TileDTO tile(tile_x, tile_y);
        tiles.push_back(tile);
    }

    return tiles;
}

void ReceiverThread::receiveGameDTO() {
    std::vector<PlayerDTO> players = receivePlayers();
    std::vector<EnemyDTO> enemies = receiveEnemies();
    std::vector<BulletDTO> bullets = receiveBullets();
    std::vector<ItemDTO> items = receiveItems();
    std::vector<WeaponDTO> weapons = receiveWeapons();
    std::vector<TileDTO> tiles = receiveTiles();

    std::unique_ptr<DTO> game =
            std::make_unique<GameDTO>(players, enemies, bullets, items, weapons, tiles);
    this->deserializer.deserialize_gameMsg(game);
    std::cout << "[CLIENT RECEIVER] Game DTO received and deserialized" << std::endl;
}

void ReceiverThread::receiveGamesList() {
    uint8_t gamesAmount;
    socket->recvall(&gamesAmount, sizeof(uint8_t), &closed);
    std::cout << "[CLIENT RECEIVER] Number of games: " << static_cast<int>(gamesAmount)
              << std::endl;

    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        std::cout << "[CLIENT RECEIVER] Connection closed, exiting receiveGamesList" << std::endl;
        return;
    }
    uint8_t games = ntohl(gamesAmount);
    std::map<uint8_t, GameInfo> gamesMap;
    for (int i = 0; i < games; i++) {
        uint8_t gameId;
        socket->recvall(&gameId, sizeof(uint8_t), &closed);
        std::cout << "[CLIENT RECEIVER] Game ID: " << static_cast<int>(gameId) << std::endl;

        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            std::cout << "[CLIENT RECEIVER] Connection closed, exiting receiveGamesList"
                      << std::endl;
            return;
        }
        uint8_t id = ntohl(gameId);
        char nameLength;
        socket->recvall(&nameLength, sizeof(char), &closed);
        std::cout << "[CLIENT RECEIVER] Game name length: " << static_cast<int>(nameLength)
                  << std::endl;

        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            std::cout << "[CLIENT RECEIVER] Connection closed, exiting receiveGamesList"
                      << std::endl;
            return;
        }
        std::string name;
        name.resize(nameLength);
        socket->recvall(&name[0], nameLength, &closed);
        std::cout << "[CLIENT RECEIVER] Game name: " << name << std::endl;

        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            std::cout << "[CLIENT RECEIVER] Connection closed, exiting receiveGamesList"
                      << std::endl;
            return;
        }
        uint8_t maxPlayers;
        socket->recvall(&maxPlayers, sizeof(uint8_t), &closed);
        std::cout << "[CLIENT RECEIVER] Max players: " << static_cast<int>(maxPlayers) << std::endl;

        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            std::cout << "[CLIENT RECEIVER] Connection closed, exiting receiveGamesList"
                      << std::endl;
            return;
        }
        uint8_t max = ntohl(maxPlayers);
        uint8_t currentPlayers;
        socket->recvall(&currentPlayers, sizeof(uint8_t), &closed);
        std::cout << "[CLIENT RECEIVER] Current players: " << static_cast<int>(currentPlayers)
                  << std::endl;

        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            std::cout << "[CLIENT RECEIVER] Connection closed, exiting receiveGamesList"
                      << std::endl;
            return;
        }
        uint8_t current = ntohl(currentPlayers);

        GameInfo gameInfo = GameInfo(id, name, max, current);
        gamesMap[id] = gameInfo;
    }
    std::unique_ptr<DTO> message = std::make_unique<GamesListDTO>(gamesMap);
    this->deserializer.deserialize_lobbyMsg(message);
    std::cout << "[CLIENT RECEIVER] Games list received and deserialized" << std::endl;
}

void ReceiverThread::receiveLobbyDTO() {
    char lobbyTypeChar;
    socket->recvall(&lobbyTypeChar, sizeof(char), &closed);
    std::cout << "[CLIENT RECEIVER] Received lobby type: " << static_cast<int>(lobbyTypeChar)
              << std::endl;

    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        std::cout << "[CLIENT RECEIVER] Connection closed, exiting receiveLobbyDTO" << std::endl;
        return;
    }
    if (!DTOValidator::validateLobbyState(lobbyTypeChar)) {
        std::cout << "[CLIENT RECEIVER] Invalid lobby state received, ignoring" << std::endl;
        return;
    }
    auto lobbyState = static_cast<LobbyState>(lobbyTypeChar);
    if (lobbyState == LobbyState::GAMES_LIST) {
        this->receiveGamesList();
    }
}

void ReceiverThread::run() {
    uint8_t playerId;
    socket->recvall(&playerId, sizeof(uint8_t), &closed);
    std::cout << "[CLIENT RECEIVER] Player ID: " << static_cast<int>(playerId) << std::endl;
    this->deserializer.setPlayerId(playerId);

    while (!this->was_closed.load() && _keep_running) {
        try {
            char dtoTypeChar;
            socket->recvall(&dtoTypeChar, sizeof(char), &closed);
            std::cout << "[CLIENT RECEIVER] Received DTO type: " << static_cast<int>(dtoTypeChar)
                      << std::endl;

            this->was_closed.store(closed);
            if (this->was_closed.load()) {
                std::cout << "[CLIENT RECEIVER] Connection closed, exiting run loop" << std::endl;
                return;
            }
            if (!DTOValidator::validateDTOType(dtoTypeChar)) {
                std::cout << "[CLIENT RECEIVER] Invalid DTO type received, ignoring" << std::endl;
                continue;
            }
            auto dtoType = static_cast<DTOType>(dtoTypeChar);
            std::cout << "[CLIENT RECEIVER] DTO type post cast: " << static_cast<int>(dtoType)
                      << std::endl;
            switch (dtoType) {
                case DTOType::GAME_DTO:
                    std::cout << "[CLIENT RECEIVER] Receiving game DTO." << std::endl;
                    this->receiveGameDTO();
                    break;
                case DTOType::COMMAND_DTO:
                    std::cout << "[CLIENT RECEIVER] Receiving command DTO." << std::endl;
                    this->receiveCommandDTO();
                    break;
                default:
                    std::cout << "[CLIENT RECEIVER] Unknown DTO type received." << std::endl;
                    break;
            }
        } catch (const std::exception& e) {
            if (!this->was_closed.load() || _keep_running) {
                std::cerr << "[CLIENT RECEIVER] ReceiverThread error: " << e.what() << std::endl;
            }
        }
    }
}
