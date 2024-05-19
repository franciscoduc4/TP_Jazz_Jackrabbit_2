#include "listGamesCommand.h"


ListGamesCommand::ListGamesCommand(std::string args): args(std::move(args)) {}

ProtocolMessage ListGamesCommand::exec(GameMonitor& gameMonitor, Protocol&& protocol,
                                       bool inLobby) {
    std::string gamesList;
    gameMonitor.listGames(gamesList);
    return ProtocolMessage(static_cast<uint8_t>(0x04), gamesList);
}
