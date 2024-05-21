#ifndef SERVER_CLIENT_ACCEPTOR_H_
#define SERVER_CLIENT_ACCEPTOR_H_

#include <atomic>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <sys/socket.h>

#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../../Common/thread.h"
#include "../Game/gameMonitor.h"
#include "../Game/player.h"

#include "lobbyPlayerThread.h"

class AcceptorThread: public Thread {
private:
    Socket serverSocket;
    std::atomic<bool> isAlive{true};
    GameMonitor gameMonitor;
    std::vector<std::unique_ptr<LobbyPlayerThread>> lobbyPlayers;

public:
    AcceptorThread(const std::string& servname);

    virtual void run() override;
    virtual void stop() override;
    void movePlayerToLobby(Socket&& socket, GameMonitor& gameMonitor);
    void cleanInactiveLobbyPlayers();
    void cleanLobby();
};

#endif  // SERVER_CLIENT_ACCEPTOR_H_
