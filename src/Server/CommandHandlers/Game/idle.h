#ifndef IDLE_HANDLER_H_
#define IDLE_HANDLER_H_

#include "../../../Common/DTO/command.h"

#include "gameCommand.h"

class IdleHandler: public GameCommandHandler {
private:
    std::unique_ptr<CommandDTO> idleCommand;

public:
    explicit IdleHandler(std::unique_ptr<CommandDTO> idleCommand);

    virtual void execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime);
};

#endif  // IDLE_HANDLER_H_