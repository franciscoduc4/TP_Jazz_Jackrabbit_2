#ifndef JUMP_HANDLER_H_
#define JUMP_HANDLER_H_

#include "../../Common/DTO/command.h"

#include "gameCommand.h"

class JumpHandler: public GameCommandHandler {
private:
    std::unique_ptr<CommandDTO> moveCommand;

public:
    explicit JumpHandler(std::unique_ptr<CommandDTO> moveCommand);

    virtual void execute(Game& game, std::atomic<bool>& keepRunning, double deltaTime);
};

#endif  // JUMP_HANDLER_H_