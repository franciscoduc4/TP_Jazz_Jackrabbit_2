#include "lobbyCommand.h"

LobbyCommand::getCommand(Command command) {
    switch (command) {
        case Command::JOIN:
            return new LobbyCommandJoin();
        case Command::CREATE:
            return new LobbyCommandCreate();
        case Command::LIST:
            return new LobbyCommandList();
        case Command::START:
            return new LobbyCommandStart();
        case Command::EXIT:
            return new LobbyCommandExit();
        default:
            return nullptr;
    }
}
