#ifndef SERVER_PLAYER_HANDLER_H_
#define SERVER_PLAYER_HANDLER_H_

#include <atomic>
#include <memory>

#include "../Common/gameTypes.h"
#include "../Common/queue.h"
#include "Common/queue.h"
#include "Common/socket.h"

#include "gamesMonitor.h"
#include "protocol.h"
#include "receiverThread.h"
#include "senderThread.h"

class PlayerHandler {
private:
    std::atomic<bool> playerIsAlive{true};
    Protocol protocol;
    GamesMonitor& gamesMonitor;
    Queue<GameTypes::Action>& actionQueue;
    ClientReceiver receiver;
    ClientSender sender;
    std::shared_ptr<Queue<GameTypes::Action>>& gameQueue;

public:
    PlayerHandler(Socket&& playerSocket, GamesMonitor& gamesMonitor,
                  std::shared_ptr<Queue<GameTypes::Action>>& actionQueue);
    void run();
    void stop();
    void join();
    bool isAlive();
};

#endif  // SERVER_PLAYER_HANDLER_H_
