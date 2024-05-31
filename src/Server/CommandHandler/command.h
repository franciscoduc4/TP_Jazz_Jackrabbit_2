#ifndef COMMAND_HANDLER_H_
#define COMMAND_HANDLER_H_

#include <memory>
#include "../../Common/queue.h"
#include "../../Common/DTO/command.h"
#include "../../Common/DTO/lobby.h"
#include "../../Common/Types/command.h"
#include "../Game/gameMonitor.h"


class CommandHandler {
public:
    virtual std::unique_ptr<LobbyDTO> execute(
            GameMonitor& gameMonitor, std::atomic<bool>& inGame,
            std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue) = 0;
    static std::unique_ptr<CommandHandler> createHandler(std::unique_ptr<CommandDTO> command);
};

#endif  // COMMAND_HANDLER_H_
