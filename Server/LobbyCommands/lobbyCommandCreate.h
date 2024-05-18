#ifndef LOBBY_COMMANDS_CREATE_H_
#define LOBBY_COMMANDS_CREATE_H_

#include "../gameMonitor.h"

#include "lobbyCommand.h"

class LobbyCommandsCreate: public LobbyCommand {
public:
    explicit LobbyCommandsCreate() {}

    void exec(GameMonitor& gameMonitor, Player&& player) override;
};

#endif  // LOBBY_COMMANDS_CREATE_H_