#include "lobbyCommand.h"

#include "../../Common/Constants/lobbyCommands.h"

#include "createGameCommand.h"
#include "invalidCommand.h"
#include "joinGameCommand.h"
#include "listGamesCommand.h"

std::unique_ptr<LobbyCommand> LobbyCommand::getCommand(ProtocolMessage message) {

    switch (message.cmd) {
        case 0x02:
            return std::make_unique<CreateGameCommand>(message.args);
        case 0x03:
            return std::make_unique<JoinGameCommand>(message.args);
        case 0x04:
            return std::make_unique<ListGamesCommand>(message.args);
        default:
            return std::make_unique<InvalidCommand>(message.args);
    }
}
