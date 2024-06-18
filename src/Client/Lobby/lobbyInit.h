#ifndef CLIENT_LOBBY_LOBBYINIT_H
#define CLIENT_LOBBY_LOBBYINIT_H

#include "../../Common/Types/lobbyMessage.h"
#include <utility>

class LobbyInit {
public:
    LobbyInit();
    std::pair<bool, LobbyMessage> launchQT(LobbyController& controller, bool& clientJoinedGame);
};

#endif  // CLIENT_LOBBY_LOBBYINIT_H
