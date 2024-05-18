#ifndef CREATE_GAME_COMMAND_H_
#define CREATE_GAME_COMMAND_H_

#include "../Game/gameMonitor.h"

#include "lobbyCommand.h"

class CreateGameCommand: public LobbyCommand {
private:
    std::string args;

public:
    explicit CreateGameCommand(std::string args);

    ProtocolMessage exec(GameMonitor& gameMonitor, Player&& player, bool inLobby) override;
};

#endif  // CREATE_GAME_COMMAND_H_
