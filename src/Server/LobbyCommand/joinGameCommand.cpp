#include "joinGameCommand.h"

#include <string>


JoinGameCommand::JoinGameCommand(std::string args): args(std::move(args)) {}

ProtocolMessage JoinGameCommand::exec(GameMonitor& gameMonitor, Protocol&& protocol,
                                      bool& inLobby) {
    std::stringstream argsIt(args);

    std::string gameName;
    std::string character;

    argsIt >> gameName;
    argsIt >> character;

    Player player(std::move(protocol), character);

    gameMonitor.addPlayer(gameName, std::move(player));
    inLobby = false;

    return ProtocolMessage();
}
