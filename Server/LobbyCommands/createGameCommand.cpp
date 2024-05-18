#include "createGameCommand.h"

#include <sstream>
#include <utility>

CreateGameCommand::CreateGameCommand(std::string args): args(std::move(args)) {}

ProtocolMessage CreateGameCommand::exec(GameMonitor& gameMonitor, Player&& player, bool inLobby) {
    std::stringstream argsIt(args);

    int maxPlayers;
    std::string gameName;
    argsIt >> maxPlayers;
    argsIt >> gameName;

    gameMonitor.createGame(gameName, maxPlayers, std::move(player));
    inLobby = false;

    return ProtocolMessage();
}
