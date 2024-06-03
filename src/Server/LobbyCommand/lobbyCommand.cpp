#include "lobbyCommand.h"

#include "createGameCommand.h"
#include "invalidCommand.h"
#include "joinGameCommand.h"
#include "listGamesCommand.h"

std::unique_ptr<LobbyCommand> LobbyCommand::getCommand(ProtocolMessage message) {

    switch (static_cast<LobbyCommands>(message.cmd)) {
        case LobbyCommands::CREATE_GAME:
            return std::make_unique<CreateGameCommand>(message.args);
        case LobbyCommands::JOIN_GAME:
            return std::make_unique<JoinGameCommand>(message.args);
        case LobbyCommands::LIST_GAMES:
            return std::make_unique<ListGamesCommand>(message.args);
        default:
            return std::make_unique<InvalidCommand>(message.args);
    }
}
