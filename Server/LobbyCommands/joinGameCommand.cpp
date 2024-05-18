#include "joinGameCommand.h"

#include <sstream>

JoinGameCommand::JoinGameCommand(std::string args): args(std::move(args)) {}

ProtocolMessage JoinGameCommand::exec(GameMonitor& gameMonitor, Player&& player, bool inLobby) {
    std::stringstream argsIt(args);

    std::string gameName;
    argsIt >> gameName;

    gameMonitor.addPlayer(gameName, std::move(player));
    inLobby = false;

    return ProtocolMessage();
}
