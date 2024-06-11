#include "sender.h"

#include <memory>
#include <utility>

#include "../CommandHandlers/Lobby/lobbyCommand.h"

SenderThread::SenderThread(std::shared_ptr<Socket> socket, std::atomic<bool>& keepPlaying,
                           std::atomic<bool>& inGame, GameMonitor& gameMonitor, uint32_t playerId,
                           std::shared_ptr<Queue<std::unique_ptr<GameDTO>>> sendQueue):
        playerId(playerId),
        serializer(socket),
        deserializer(socket),
        keepPlaying(keepPlaying),
        inGame(inGame),
        wasClosed(false),
        sendQueue(sendQueue),
        recvQueue(std::make_shared<Queue<std::unique_ptr<CommandDTO>>>()),
        receiver(socket, keepPlaying, inGame, gameMonitor, playerId, recvQueue),
        gameMonitor(gameMonitor) {}

// void SenderThread::run() {
//     bool wasClosed = false;
//     std::cout << "Sender started" << std::endl;
//     serializer.sendId(playerId, wasClosed);

//     //Game dto test para sdl

//     while (keepPlaying) {
//         //runLobby(wasClosed);
//         inGame = true;
//         while (inGame) {
//             try {
//                 std::unique_ptr<GameDTO> gameDTO = sendQueue->pop();
//                 serializer.sendGameDTO(std::move(gameDTO), wasClosed);
//             } catch (const std::exception& e) {
//                 if (wasClosed) {
//                     return;
//                 }
//             }
//         }
//     }
// }

// SDL TEST
void SenderThread::run() {
    bool wasClosed = false;
    std::cout << "Sender started" << std::endl;
    serializer.sendId(playerId, wasClosed);

    // Game dto test para sdl

    while (keepPlaying) {
        // runLobby(wasClosed);
        inGame = true;
        std::vector<PlayerDTO> players;
        uint16_t x = 0;
        uint16_t y = 100;
        uint32_t playerId = 1;
        int health = 100;
        int damage = 40;
        int speed = 1;
        uint8_t weaponId = 1;
        uint16_t x_w = 2;
        uint16_t y_w = 100;
        int damage_w = 100;
        int ammo = 4;
        WeaponDTO currentWeapon(weaponId, x_w, y_w, damage_w, ammo);
        CharacterType pj_type = CharacterType::JAZZ;
        CharacterStateEntity state = CharacterStateEntity::MOVING;
        PlayerDTO player(x, y, playerId, health, damage, speed, currentWeapon, pj_type, state);
        players.push_back(player);

        uint16_t x_lori = 0;
        uint16_t y_lori = 20;
        uint32_t loriId = 2;
        CharacterType lori_type = CharacterType::SPAZ;
        PlayerDTO lori(x_lori, y_lori, loriId, health, damage, speed, currentWeapon, lori_type,
                       state);
        players.push_back(lori);

        std::vector<EnemyDTO> enemies;
        uint16_t x_enemy = 50;
        uint16_t y_enemy = 100;
        int health_enemy = 100;
        int damage_enemy = 40;
        int speed_enemy = 30;
        EnemyType enemy_type = EnemyType::WALKING_ENEMY;
        EnemyStateEntity enemy_state = EnemyStateEntity::ENEMY_WALKING;

        for (uint32_t i = 0; i < 1; i++) {
            EnemyDTO enemy(x_enemy, y_enemy, i, health_enemy, damage_enemy, speed_enemy, enemy_type,
                           enemy_state);
            enemies.push_back(enemy);
            x_enemy += 50;
            y_enemy += 5;
        }

        std::vector<BulletDTO> bullets;

        std::vector<ItemDTO> items;
        uint16_t x_item = 50;
        uint16_t y_item = 50;
        ItemType gem = ItemType::GEM;

        for (int i = 1; i > 0; i--) {
            ItemDTO item(x_item, y_item, gem);
            items.push_back(item);
            x_item += 20;
            y_item += 5;
        }


        std::vector<WeaponDTO> weapons;

        std::vector<TileDTO> tiles;
        uint16_t tile_x = 100;
        uint16_t tile_y = 100;
        TileDTO tile(tile_x, tile_y);
        tiles.push_back(tile);

        inGame = true;
        while (inGame) {
            try {
                // std::unique_ptr<GameDTO> gameDTO = sendQueue->pop();
                std::unique_ptr<GameDTO> gameDTO =
                        std::make_unique<GameDTO>(players, enemies, bullets, items, weapons, tiles);
                serializer.sendGameDTO(std::move(gameDTO), wasClosed);
            } catch (const std::exception& e) {
                if (wasClosed) {
                    return;
                }
            }
        }
    }
}

void SenderThread::runLobby(bool& wasClosed) {
    while (keepPlaying && !inGame) {
        try {
            std::cout << "Waiting for command" << std::endl;
            std::unique_ptr<CommandDTO> command = deserializer.getCommand(wasClosed, playerId);
            if (command == nullptr) {
                continue;
            }
            auto handler = LobbyCommandHandler::createHandler(std::move(command));
            auto commandDTO = handler->execute(gameMonitor, std::ref(inGame), recvQueue);
            serializer.sendCommand(std::move(commandDTO), wasClosed);
        } catch (const std::exception& e) {
            if (wasClosed) {
                return;
            }
        }
    }
    receiver.start();
}
