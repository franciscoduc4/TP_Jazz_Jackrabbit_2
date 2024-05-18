#ifndef LOBBY_PLAYER_THREAD_H_
#define LOBBY_PLAYER_THREAD_H_

#include "../Common/thread.h"

#include "gameMonitor.h"
#include "player.h"
#include "protocol.h"

class LobbyPlayerThread: public Thread {
private:
    Player player;
    GameMonitor& gameMonitor;
    bool inLobby;

public:
    LobbyPlayerThread(Player&& player, GameMonitor& gameMonitor);
    virtual void run() override;
    virtual void stop() override;
};

#endif  // LOBBY_PLAYER_THREAD_H_
