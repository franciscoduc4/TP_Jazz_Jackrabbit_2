#ifndef ACCEPTOR_THREAD_H_
#define ACCEPTOR_THREAD_H_

#include <atomic>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <sys/socket.h>

#include "../../Common/DTO/game.h"
#include "../../Common/queue.h"
#include "../../Common/queueMonitor.h"
#include "../../Common/socket.h"
#include "../../Common/thread.h"
#include "../Game/gameMonitor.h"
#include "../Game/player.h"

class AcceptorThread: public Thread {
private:
    std::shared_ptr<Socket> serverSocket;
    std::atomic<bool> isAlive{true};
    GameMonitor gameMonitor;
    std::vector<std::unique_ptr<Player>> players;
    QueueMonitor<GameDTO> queueMonitor;

public:
    explicit AcceptorThread(const std::string& servname);

    virtual void run() override;
    virtual void stop() override;
    void removeDeadPlayers();
    void removeAllPlayers();
};

#endif  // ACCEPTOR_THREAD_H_
