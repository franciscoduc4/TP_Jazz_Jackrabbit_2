#ifndef LOBBY_COMMAND_H_
#define LOBBY_COMMAND_H_

#include <memory>

#include "../../Common/Constants/lobbyCommands.h"
#include "../../Common/protocol.h"
#include "../Game/gameMonitor.h"
#include "../Game/player.h"


class LobbyCommand {
public:
    virtual ProtocolMessage exec(GameMonitor& gameMonitor, Protocol&& protocol, bool& inLobby) = 0;
    static std::unique_ptr<LobbyCommand> getCommand(ProtocolMessage message);
};

#endif  // LOBBY_COMMAND_H_
