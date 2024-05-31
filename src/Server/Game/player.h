#ifndef PLAYER_H_
#define PLAYER_H_

#include <atomic>
#include <memory>
#include <string>
#include <utility>

#include "../../Common/Models/gameTypes.h"
#include "../../Common/queue.h"
#include "../../Common/queueMonitor.h"
#include "../../Common/socket.h"
#include "../Game/gameMonitor.h"
#include "../Physics/character.h"
#include "../Threads/receiver.h"
#include "../Threads/sender.h"

class Player {
private:
    int32_t playerId;
    std::shared_ptr<Socket> socket;
    std::atomic<bool> inGame{false};
    std::atomic<bool> keepPlaying{true};
    SenderThread sender;

public:
    Player(std::shared_ptr<Socket> socket, GameMonitor& gameMonitor,
           QueueMonitor<std::shared_ptr<Queue<GameDTO>>>& queueMonitor, int32_t playerId);
    void disconnect();
    bool isPlaying() const;
};

#endif  // PLAYER_H_
