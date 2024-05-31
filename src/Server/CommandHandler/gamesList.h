#ifndef GAMES_LIST_HANDLER_H_
#define GAMES_LIST_HANDLER_H_

#include "../../Common/DTO/command.h"
#include "../../Common/DTO/lobby.h"
#include "../../Common/queue.h"
#include "../Game/gameMonitor.h"

#include "command.h"

class GamesListHandler: public CommandHandler {
private:
    std::unique_ptr<CommandDTO> command;

public:
    explicit GamesListHandler(std::unique_ptr<CommandDTO> command);

    virtual std::unique_ptr<LobbyDTO> execute(
            GameMonitor& gameMonitor, std::atomic<bool>& inGame,
            std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue) = 0;
};

#endif  // GAMES_LIST_HANDLER_H_