#include "lobbyCommand.h"


std::shared_ptr<LobbyCommand> LobbyCommand::getCommand(ProtocolMessage message) {

    switch (static_cast<LobbyCommands>(message.cmd)) {
        case LobbyCommands::CREATE_GAME:
            return std::make_shared<CreateGameCommand>(message.args);
        case LobbyCommands::JOIN_GAME:
            return std::make_shared<JoinGameCommand>(message.args);
        case LobbyCommands::LIST_GAMES:
            return std::make_shared<ListGamesCommand>(message.args);
        default:
            return std::make_shared<InvalidCommand>(message.args);
    }
}
