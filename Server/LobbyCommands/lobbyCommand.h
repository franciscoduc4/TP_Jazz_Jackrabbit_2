#ifndef LOBBY_COMMANDS_H_
#define LOBBY_COMMANDS_H_

#include "../Game/gameMonitor.h"
#include "../Game/player.h"

class LobbyCommand {
public:
    virtual ProtocolMessage exec(GameMonitor& gameMonitor, Player&& player, bool inLobby) = 0;
    static std::unique_ptr<LobbyCommand> getCommand(ProtocolMessage message);
};

#endif  // LOBBY_COMMANDS_JOIN_H_
