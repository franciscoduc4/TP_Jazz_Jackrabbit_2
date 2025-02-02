#ifndef GAMES_LIST_HANDLER_H_
#define GAMES_LIST_HANDLER_H_

#include <memory>

#include "../../../Common/DTO/command.h"
#include "../../../Common/DTO/dto.h"
#include "../../../Common/DTO/lobby.h"
#include "../../../Common/Types/gameInfo.h"
#include "../../../Common/queue.h"
#include "../../Game/gameMonitor.h"

#include "lobbyCommand.h"

class GamesListHandler: public LobbyCommandHandler {
private:
    std::unique_ptr<CommandDTO> command;

public:
    explicit GamesListHandler(std::unique_ptr<CommandDTO> command);

    virtual void execute(GameMonitor& gameMonitor, std::atomic<bool>& inGame,
                         const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue);
};

#endif  // GAMES_LIST_HANDLER_H_
