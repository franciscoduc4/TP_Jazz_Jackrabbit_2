#ifndef CLIENT_LOBBY_LOBBYINIT_H
#define CLIENT_LOBBY_LOBBYINIT_H

#include <utility>

#include "../../Common/Types/lobbyMessage.h"
#include "Types/finalStats.h"

class LobbyInit {
public:
    LobbyInit();
    std::pair<bool, LobbyMessage> launchQT(LobbyController& controller, bool& clientJoinedGame);
    void displayStats(const LobbyMessage& msg, const FinalStats& stats, bool& clientJoinedGame, const uint8_t& playerId);
};

#endif  // CLIENT_LOBBY_LOBBYINIT_H
