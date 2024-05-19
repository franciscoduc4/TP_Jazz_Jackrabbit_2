#include "invalidCommand.h"
#include <string>

InvalidCommand::InvalidCommand(std::string args): args(std::move(args)) {}

ProtocolMessage InvalidCommand::exec(GameMonitor& gameMonitor, Protocol&& protocol, bool inLobby) {
    return ProtocolMessage();
}
