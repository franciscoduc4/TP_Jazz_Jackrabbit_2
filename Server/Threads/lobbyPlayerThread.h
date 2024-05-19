#ifndef LOBBY_PLAYER_THREAD_H_
#define LOBBY_PLAYER_THREAD_H_

#include "../../Common/protocol.h"
#include "../../Common/thread.h"
#include "../Game/gameMonitor.h"
#include "../Game/player.h"
#include "../LobbyCommand/lobbyCommand.h"

class LobbyPlayerThread: public Thread {
private:
    Protocol protocol;
    GameMonitor& gameMonitor;
    bool inLobby;

public:
    LobbyPlayerThread(Socket&& playerSocket, GameMonitor& gameMonitor);
    virtual void run() override;
    virtual void stop() override;
    void handleCommand(Protocol& protocol, const std::shared_ptr<LobbyCommand>& lobbyCommand);
    bool isInLobby() const;
};

#endif  // LOBBY_PLAYER_THREAD_H_
