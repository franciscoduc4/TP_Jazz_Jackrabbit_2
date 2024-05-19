#ifndef LOBBY_COMMAND_H_
#define LOBBY_COMMAND_H_

#include <memory>

#include "../../Common/Constants/lobbyCommands.h"
#include "../Game/gameMonitor.h"
#include "../Game/player.h"

#include "createGameCommand.h"
#include "invalidCommand.h"
#include "joinGameCommand.h"
#include "listGamesCommand.h"

class LobbyCommand {
public:
    virtual ProtocolMessage exec(GameMonitor& gameMonitor, Protocol&& protocol, bool inLobby) = 0;
    static std::shared_ptr<LobbyCommand> getCommand(ProtocolMessage message);
};

#endif  // LOBBY_COMMAND_H_
