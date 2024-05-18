#include "invalidCommand.h"

#include <sstream>
#include <utility>

InvalidCommand::InvalidCommand(std::string args): args(std::move(args)) {}

ProtocolMessage InvalidCommand::exec(GameMonitor& gameMonitor, Player&& player, bool inLobby) {
    return ProtocolMessage();
}
