#ifndef GAMES_LIST_HANDLER_H_
#define GAMES_LIST_HANDLER_H_

#include <memory>
#include "../../../Common/Types/gameInfo.h"
#include "../../../Common/DTO/command.h"
#include "../../../Common/DTO/lobby.h"
#include "../../../Common/queue.h"
#include "../../Game/gameMonitor.h"
#include "../../../Common/DTO/dto.h"

#include "lobbyCommand.h"

class GamesListHandler: public LobbyCommandHandler {
private:
    std::unique_ptr<CommandDTO> command;

public:
    explicit GamesListHandler(std::unique_ptr<CommandDTO> command);

    virtual std::unique_ptr<CommandDTO> execute(
            GameMonitor& gameMonitor, std::atomic<bool>& inGame,
            std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
            std::shared_ptr<Queue<std::unique_ptr<GameDTO>>> sendQueue);
};

#endif  // GAMES_LIST_HANDLER_H_
