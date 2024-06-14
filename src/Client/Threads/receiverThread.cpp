#include "./receiverThread.h"

#include <netinet/in.h>

#include "../../Common/Types/command.h"
#include "../../Common/Types/entity.h"
#include "DTO/startGame.h"
#include "DTO/createGame.h"

ReceiverThread::ReceiverThread(Deserializer& deserializer, std::shared_ptr<Socket>& socket,
                               std::atomic<bool>& was_closed):
        deserializer(deserializer), socket(socket), was_closed(was_closed), closed(false) {}

void ReceiverThread::receiveCommandDTO() {
    char lobbyTypeChar;
    socket->recvall(&lobbyTypeChar, sizeof(char), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        return;
    }
    if (lobbyTypeChar == static_cast<char>(Command::START_GAME)) {
        uint32_t gameId;
        this->socket->recvall(&gameId, sizeof(uint32_t), &closed);
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            return;
        }
        uint32_t id = ntohl(gameId);
        std::unique_ptr<DTO> dto = std::make_unique<StartGameDTO>(id);
        this->deserializer.deserialize_lobbyMsg(dto);
    } else if (lobbyTypeChar == static_cast<char>(Command::CREATE_GAME)) {
        uint32_t gameId;
        this->socket->recvall(&gameId, sizeof(uint32_t), &closed);
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            return;
        }
        uint32_t id = ntohl(gameId);
        std::unique_ptr<DTO> cgDto = std::make_unique<CreateGameDTO>(id);
        this->deserializer.deserialize_lobbyMsg(cgDto);
    }
    /*if (!DTOValidator::validateLobbyState(lobbyTypeChar)) {
        return;
    }*/
    auto lobbyState = static_cast<LobbyState>(lobbyTypeChar);
    if (lobbyState == LobbyState::GAMES_LIST) {
        this->receiveGamesList();
    }
}

std::vector<PlayerDTO> ReceiverThread::receivePlayers() {
    std::vector<PlayerDTO> players;
    uint8_t cant_jugadores;

    this->socket->recvall(&cant_jugadores, sizeof(uint8_t), &closed);
    uint8_t aux;
    for (uint8_t i = 0; i < cant_jugadores; i++) {
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint32_t playerId = static_cast<uint32_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int damage = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int health = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int speed = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int getRespawnTime = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t x = static_cast<uint16_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t y = static_cast<uint16_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        CharacterType pj_type = static_cast<CharacterType>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        CharacterStateEntity state = static_cast<CharacterStateEntity>(aux);
        WeaponDTO weapon(0, 0, 0, 0, 0);  // PRUEBA CON UN WEAPON CUALQUIERA
        PlayerDTO player(x, y, playerId, health, damage, speed, weapon, pj_type, state);
        players.push_back(player);
    }

    // WeaponDTO weapon(0, 0, 0, 0, 0);
    // PlayerDTO player(0, 0, 0, 100, 50, 2, weapon, CharacterType::JAZZ,
    // CharacterStateEntity::MOVING); players.push_back(player); PlayerDTO player2(50, 50, 1, 100,
    // 50, 2, weapon, CharacterType::LORI, CharacterStateEntity::MOVING);
    // players.push_back(player2);
    return players;
}

std::vector<EnemyDTO> ReceiverThread::receiveEnemies() {
    std::vector<EnemyDTO> enemies;
    uint8_t cant_enemies;

    this->socket->recvall(&cant_enemies, sizeof(uint8_t), &closed);
    uint8_t aux;
    for (uint8_t i = 0; i < cant_enemies; i++) {
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint32_t enemyId = static_cast<uint32_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int enemy_damage = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int enemy_health = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int enemy_speed = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t enemy_x = static_cast<uint16_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t enemy_y = static_cast<uint16_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        EnemyType enemy_type = static_cast<EnemyType>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        EnemyStateEntity enemy_state = static_cast<EnemyStateEntity>(aux);
        EnemyDTO enemy(enemy_x, enemy_y, enemyId, enemy_health, enemy_damage, enemy_speed,
                       enemy_type, enemy_state);
        enemies.push_back(enemy);
    }

    // EnemyDTO enemy(50, 30, 0, 100, 20, 1, EnemyType::WALKING_ENEMY,
    // EnemyStateEntity::ENEMY_WALKING); enemies.push_back(enemy);
    return enemies;
}

std::vector<BulletDTO> ReceiverThread::receiveBullets() {
    std::vector<BulletDTO> bullets;
    uint8_t cant_bullets;

    this->socket->recvall(&cant_bullets, sizeof(uint8_t), &closed);
    uint8_t aux;
    for (uint8_t i = 0; i < cant_bullets; i++) {
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint32_t bulletId = static_cast<uint32_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int bullet_damage = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int bullet_speed = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t bullet_x = static_cast<uint16_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t bullet_y = static_cast<uint16_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int shooterId = static_cast<int>(aux);
        BulletDTO bullet(bullet_x, bullet_y, bulletId, bullet_damage, bullet_speed, shooterId);
        bullets.push_back(bullet);
    }

    // BulletDTO bullet(150, 60, 0, 10, 5, 3);
    // bullets.push_back(bullet);
    return bullets;
}

std::vector<ItemDTO> ReceiverThread::receiveItems() {
    std::vector<ItemDTO> items;
    uint8_t cant_items;
    this->socket->recvall(&cant_items, sizeof(uint8_t), &closed);
    uint8_t aux;
    for (uint8_t i = 0; i < cant_items; i++) {
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t item_x = static_cast<uint16_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t item_y = static_cast<uint16_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        ItemType item_type = static_cast<ItemType>(aux);
        ItemDTO item(item_x, item_y, item_type);
        items.push_back(item);
    }
    // ItemDTO item(80, 80, ItemType::GEM);
    // items.push_back(item);
    return items;
}

std::vector<WeaponDTO> ReceiverThread::receiveWeapons() {
    std::vector<WeaponDTO> weapons;
    uint8_t cant_weapons;

    this->socket->recvall(&cant_weapons, sizeof(uint8_t), &closed);
    uint8_t aux;
    for (uint8_t i = 0; i < cant_weapons; i++) {
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint8_t weaponId = static_cast<uint8_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int weapon_damage = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int weapon_ammo = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int shoot_speed = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t weapon_x = static_cast<uint16_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t weapon_y = static_cast<uint16_t>(aux);

        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint32_t bulletId = static_cast<uint32_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int bullet_damage = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int bullet_speed = static_cast<int>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t bullet_x = static_cast<uint16_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t bullet_y = static_cast<uint16_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        int shooterId = static_cast<int>(aux);

        WeaponDTO weapon(weaponId, weapon_x, weapon_y, weapon_damage, weapon_ammo);
        weapons.push_back(weapon);
    }

    return weapons;
}

std::vector<TileDTO> ReceiverThread::receiveTiles() {
    std::vector<TileDTO> tiles;
    uint8_t cant_tiles;

    this->socket->recvall(&cant_tiles, sizeof(uint8_t), &closed);
    uint8_t aux;
    for (uint8_t i = 0; i < cant_tiles; i++) {
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t tile_x = static_cast<uint16_t>(aux);
        this->socket->recvall(&aux, sizeof(uint8_t), &closed);
        uint16_t tile_y = static_cast<uint16_t>(aux);

        TileDTO tile(tile_x, tile_y);
        tiles.push_back(tile);
    }

    // TileDTO tile(6, 80);
    // tiles.push_back(tile);
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
}

void ReceiverThread::receiveGamesList() {
    uint32_t gamesAmount;
    socket->recvall(&gamesAmount, sizeof(uint32_t), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        return;
    }
    uint32_t games = ntohl(gamesAmount);
    std::map<uint32_t, GameInfo> gamesMap;
    for (int i = 0; i < games; i++) {
        uint32_t gameId;
        socket->recvall(&gameId, sizeof(uint32_t), &closed);
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            return;
        }
        uint32_t id = ntohl(gameId);
        char nameLength;
        socket->recvall(&nameLength, sizeof(char), &closed);
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
        uint32_t maxPlayers;
        socket->recvall(&maxPlayers, sizeof(uint32_t), &closed);
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            return;
        }
        uint32_t max = ntohl(maxPlayers);
        uint32_t currentPlayers;
        socket->recvall(&currentPlayers, sizeof(uint32_t), &closed);
        this->was_closed.store(closed);
        if (this->was_closed.load()) {
            return;
        }
        uint32_t current = ntohl(currentPlayers);

        GameInfo gameInfo = GameInfo(id, name, max, current);
        gamesMap[id] = gameInfo;
    }
    std::unique_ptr<DTO> message = std::make_unique<GamesListDTO>(gamesMap);
    this->deserializer.deserialize_lobbyMsg(message);
}

void ReceiverThread::receiveLobbyDTO() {
    char lobbyTypeChar;
    socket->recvall(&lobbyTypeChar, sizeof(char), &closed);
    this->was_closed.store(closed);
    if (this->was_closed.load()) {
        return;
    }
    if (!DTOValidator::validateLobbyState(lobbyTypeChar)) {
        return;
    }
    auto lobbyState = static_cast<LobbyState>(lobbyTypeChar);
    if (lobbyState == LobbyState::GAMES_LIST) {
        this->receiveGamesList();
    }
}

void ReceiverThread::run() {
    uint32_t playerId;
    socket->recvall(&playerId, sizeof(uint32_t), &closed);
    playerId = ntohl(playerId);
    std::cout << "Player ID: " << playerId << std::endl;
    this->deserializer.setPlayerId(playerId);

    while (!this->was_closed.load() && _keep_running) {
        try {

            char dtoTypeChar;
            socket->recvall(&dtoTypeChar, sizeof(char), &closed);
            std::cout << "Received DTO type: " << static_cast<int>(dtoTypeChar) << std::endl;
            this->was_closed.store(closed);
            if (this->was_closed.load()) {
                return;
            }
            /*
            if (!DTOValidator::validateDTOType(dtoTypeChar)) {
                continue;
            }
            auto dtoType = static_cast<DTOType>(dtoTypeChar);
            std::cout << "DTO type post cast: " << static_cast<int>(dtoType) << std::endl;
            switch (dtoType) {
                case DTOType::GAME_DTO:
                    this->receiveGameDTO();
                    break;
                // case DTOType::LOBBY_DTO:
                //     this->receiveLobbyDTO();
                //     break;
                case DTOType::COMMAND_DTO:
                    this->receiveCommandDTO();
                    break;
                default:
                    break;
            } 
           */
          this->receiveGameDTO();
        } catch (const std::exception& e) {
            if (!this->was_closed.load() || _keep_running) {
                std::cerr << "ReceiverThread error: " << e.what() << std::endl;
            }
        }
    }
}
