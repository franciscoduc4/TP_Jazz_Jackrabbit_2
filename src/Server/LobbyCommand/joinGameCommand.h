#ifndef JOIN_GAME_COMMAND_H_
#define JOIN_GAME_COMMAND_H_

#include <sstream>
#include <string>
#include <utility>

#include "../../Common/protocol.h"
#include "../Game/gameMonitor.h"

#include "lobbyCommand.h"

class JoinGameCommand: public LobbyCommand {
private:
    std::string args;

public:
    explicit JoinGameCommand(std::string args);

    ProtocolMessage exec(GameMonitor& gameMonitor, Protocol&& protocol, bool& inLobby) override;
};

#endif  // JOIN_GAME_COMMAND_H_
