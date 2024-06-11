#ifndef CLIENT_RECEIVER_THREAD_H
#define CLIENT_RECEIVER_THREAD_H

#include "../../Common/thread.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../../Client/Protocol/deserializer.h"
#include "../../Common/DTO/player.h"
#include "../../Common/DTO/game.h"
#include "../../Common/DTO/weapon.h"
#include "../../Common/DTO/bullet.h"
#include "../../Common/DTO/enemy.h"
#include "../../Common/DTO/tile.h"


#include <atomic>
#include <memory>
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


    void receiveLobbyDTO();
    void receiveGamesList();
    void receiveGameUpdate();
    void receiveCommandDTO();
    

public:
    ReceiverThread(Deserializer& deserializer, std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed);
    void run() override;

};

#endif  // CLIENT_RECEIVER_THREAD_H
