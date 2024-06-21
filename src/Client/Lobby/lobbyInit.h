#ifndef CLIENT_LOBBY_LOBBYINIT_H
#define CLIENT_LOBBY_LOBBYINIT_H

#include <utility>

#include "../../Common/Types/lobbyMessage.h"
#include "Types/finalStats.h"

class LobbyInit {
public:
    LobbyInit();
    std::pair<bool, LobbyMessage> launchQT(LobbyController& controller, bool& clientJoinedGame);
    void displayStats(FinalStats stats, bool& clientJoinedGame);
};

#endif  // CLIENT_LOBBY_LOBBYINIT_H
