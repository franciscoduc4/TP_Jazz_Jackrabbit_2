#include "createGameCommand.h"


CreateGameCommand::CreateGameCommand(std::string args): args(std::move(args)) {}

ProtocolMessage CreateGameCommand::exec(GameMonitor& gameMonitor, Protocol&& protocol,
                                        bool inLobby) {
    std::stringstream argsIt(args);

    int maxPlayers;
    std::string gameName;
    argsIt >> maxPlayers;
    argsIt >> gameName;

    Player player(std::move(protocol));
    gameMonitor.createGame(gameName, maxPlayers, std::move(player));
    inLobby = false;

    return ProtocolMessage();
}
