#ifndef SERVER_CLIENT_ACCEPTOR_H_
#define SERVER_CLIENT_ACCEPTOR_H_

#include <atomic>
#include <string>
#include <vector>

#include "../Common/queue.h"
#include "../Common/socket.h"
#include "../Common/thread.h"

#include "gameMonitor.h"
#include "lobbyPlayerThread.h"
#include "player.h"

class AcceptorThread: public Thread {
private:
    Socket serverSocket;
    std::atomic<bool> isAlive{true};
    GameMonitor gameMonitor;
    std::vector<LobbyPlayerThread> lobbyPlayers;

public:
    AcceptorThread(const std::string& servname, GameMonitor& gameMonitor);

    virtual void run() override;
    virtual void stop() override;
    void movePlayerToLobby(Player&& player, GameMonitor& gameMonitor);
    void cleanInactiveLobbyPlayers();
    void cleanLobby();
};

#endif  // SERVER_CLIENT_ACCEPTOR_H_
