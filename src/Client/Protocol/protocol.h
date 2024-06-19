#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <memory>
#include <atomic>
#include <netinet/in.h>

#include "../../Common/socket.h"

// DTOs
#include "../../Common/DTO/player.h"
#include "../../Common/DTO/game.h"
#include "../../Common/DTO/weapon.h"
#include "../../Common/DTO/bullet.h"
#include "../../Common/DTO/enemy.h"
#include "../../Common/DTO/tile.h"
#include "../../Common/DTO/mapsList.h"
#include "../../Common/DTO/gamesList.h"
#include "../../Common/DTO/startGame.h"
#include "../../Common/DTO/createGame.h"
#include "../../Common/DTO/gameUpdate.h"

// Types
#include "../../Common/Types/command.h"
#include "../../Common/Types/entity.h"
#include "../../Common/dtoValidator.h"

class ClientProtocol {
private:
    std::shared_ptr<Socket>& socket;
    std::atomic<bool>& was_closed;
    bool closed;

    GameInfo receiveGameInfo();
    bool receive_uint8(uint8_t& value);
    bool receive_uint32(uint32_t& value);
    bool receive_char(char& value);
    bool receive_string(const uint8_t& length, std::string& value);
public:
    ClientProtocol(std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed);
    // States
    bool isClosed();
    // Connection
    void close();
    void closeSocket();
    // Player ID
    void receivePlayerId(uint8_t& playerId);
    // DTO Type
    void receiveDTOType(char& dtoType);
    // Lobby
    void receiveGamesList(std::unique_ptr<DTO>& dto);
    void receiveMapsList(std::unique_ptr<DTO>& dto);
    void receiveGameUpdate(std::unique_ptr<DTO>& dto);
    void receiveCommandDTO(std::unique_ptr<DTO>& dto);

    // Gameplay
    void receiveGameDTO(std::unique_ptr<DTO>& dto);
    std::vector<PlayerDTO> receivePlayers();
    std::vector<EnemyDTO> receiveEnemies();
    std::vector<BulletDTO> receiveBullets();
    std::vector<ItemDTO> receiveItems();
    std::vector<WeaponDTO> receiveWeapons();
    std::vector<TileDTO> receiveTiles();
};

#endif  // CLIENT_PROTOCOL_H
