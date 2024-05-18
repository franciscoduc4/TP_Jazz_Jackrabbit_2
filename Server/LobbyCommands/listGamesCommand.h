#ifndef LIST_GAMES_COMMAND_H_
#define LIST_GAMES_COMMAND_H_

#include "../Game/gameMonitor.h"

#include "lobbyCommand.h"

class ListGamesCommand: public LobbyCommand {
private:
    std::string args;

public:
    explicit ListGamesCommand(std::string args);

    ProtocolMessage exec(GameMonitor& gameMonitor, Player&& player, bool inLobby) override;
};

#endif  // LIST_GAMES_COMMAND_H_
