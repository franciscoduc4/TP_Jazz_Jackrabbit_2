#ifndef LOBBY_PLAYER_THREAD_H_
#define LOBBY_PLAYER_THREAD_H_

#include "../Common/protocol.h"
#include "../Common/thread.h"

#include "gameMonitor.h"
#include "player.h"

class LobbyPlayerThread: public Thread {
private:
    Player player;
    GameMonitor& gameMonitor;
    bool inLobby;
    Protocol protocol;

public:
    LobbyPlayerThread(Player&& player, GameMonitor& gameMonitor);
    virtual void run() override;
    virtual void stop() override;

    bool isInLobby() const;
};

#endif  // LOBBY_PLAYER_THREAD_H_
