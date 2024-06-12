#ifndef EPISODES_LIST_HANDLER_H_
#define EPISODES_LIST_HANDLER_H_

#include <memory>

#include "../../../Common/DTO/command.h"
#include "../../../Common/DTO/dto.h"
#include "../../../Common/queue.h"
#include "../../Game/gameMonitor.h"

#include "lobbyCommand.h"

class EpisodesListHandler: public LobbyCommandHandler {
private:
    std::unique_ptr<CommandDTO> command;

public:
    explicit EpisodesListHandler(std::unique_ptr<CommandDTO> command);

    virtual void execute(GameMonitor& gameMonitor, std::atomic<bool>& inGame,
                         std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                         std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue);
};

#endif  // EPISODES_LIST_HANDLER_H_
