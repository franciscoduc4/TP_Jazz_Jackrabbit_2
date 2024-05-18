#include "listGamesCommand.h"

#include <sstream>

#include "../../Common/protocol.h"

ListGamesCommand::ListGamesCommand(std::string args): args(std::move(args)) {}

ProtocolMessage ListGamesCommand::exec(GameMonitor& gameMonitor, Player&& player, bool inLobby) {
    std::string gamesList;
    gameMonitor.listGames(gamesList);
    return ProtocolMessage(static_cast<uint8_t>(0x04), gamesList);
}
