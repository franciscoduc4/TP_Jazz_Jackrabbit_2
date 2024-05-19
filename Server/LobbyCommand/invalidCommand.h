#ifndef INVALID_COMMAND_H_
#define INVALID_COMMAND_H_

#include <utility>
#include <string>
#include "../Game/gameMonitor.h"
#include "lobbyCommand.h"

class InvalidCommand: public LobbyCommand {
private:
    std::string args;

public:
    explicit InvalidCommand(std::string args);

    ProtocolMessage exec(GameMonitor& gameMonitor, Protocol&& protocol, bool inLobby) override;
};

#endif  // INVALID_COMMAND_H_
