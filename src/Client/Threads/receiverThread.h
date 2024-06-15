#ifndef CLIENT_RECEIVER_THREAD_H
#define CLIENT_RECEIVER_THREAD_H

#include <netinet/in.h>
#include <atomic>
#include <memory>
#include <unordered_map>

#include "../../Common/thread.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../../Client/Protocol/deserializer.h"

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

// Types
#include "../../Common/Types/command.h"
#include "../../Common/Types/entity.h"

#include "../../Common/dtoValidator.h"

class ReceiverThread : public Thread {
private:
    Deserializer& deserializer;
    std::shared_ptr<Socket>& socket;
    std::atomic<bool>& was_closed;
    bool closed;

    void receiveGameDTO();
    std::vector<PlayerDTO> receivePlayers();
    std::vector<EnemyDTO> receiveEnemies();
    std::vector<BulletDTO> receiveBullets();
    std::vector<ItemDTO> receiveItems();
    std::vector<WeaponDTO> receiveWeapons();
    std::vector<TileDTO> receiveTiles();


    // Lobby Receives
    void receiveLobbyDTO();
    void receiveGamesList();
    void receiveMapsList();
    void receiveGameUpdate();
    void receiveCommandDTO();
    

public:
    ReceiverThread(Deserializer& deserializer, std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed);
    void run() override;

};

#endif  // CLIENT_RECEIVER_THREAD_H
