#ifndef LOBBY_COMMAND_HANDLER_H_
#define LOBBY_COMMAND_HANDLER_H_

#include <memory>

#include "../../../Common/DTO/command.h"
#include "../../../Common/DTO/lobby.h"
#include "../../../Common/Types/command.h"
#include "../../../Common/queue.h"
#include "../../Game/gameMonitor.h"


class LobbyCommandHandler {
public:
    virtual std::unique_ptr<LobbyDTO> execute(
            GameMonitor& gameMonitor, std::atomic<bool>& inGame,
            std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue) = 0;
    static std::unique_ptr<LobbyCommandHandler> createHandler(std::unique_ptr<CommandDTO> command);
};

#endif  // LOBBY_COMMAND_HANDLER_H_
