#include "joinGameCommand.h"


JoinGameCommand::JoinGameCommand(std::string args): args(std::move(args)) {}

ProtocolMessage JoinGameCommand::exec(GameMonitor& gameMonitor, Protocol&& protocol, bool inLobby) {
    std::stringstream argsIt(args);

    std::string gameName;
    argsIt >> gameName;

    Player player(std::move(protocol));
    gameMonitor.addPlayer(gameName, std::move(player));
    inLobby = false;

    return ProtocolMessage();
}
