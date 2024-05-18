#ifndef LOBBY_COMMANDS_H_
#define LOBBY_COMMANDS_H_

#include "../Game/gameMonitor.h"
#include "../Game/player.h"

class LobbyCommand {
public:
    virtual void exec(GameMonitor& gameMonitor, Player&& player) = 0;
    LobbyCommand getCommand(Command command);
};

#endif  // LOBBY_COMMANDS_JOIN_H_

