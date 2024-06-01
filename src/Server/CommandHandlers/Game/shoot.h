#ifndef SHOOT_HANDLER_H_
#define SHOOT_HANDLER_H_

#include "../../Common/DTO/command.h"

#include "gameCommand.h"

class ShootHandler: public GameCommandHandler {
private:
    std::unique_ptr<CommandDTO> shootCommand;

public:
    explicit ShootHandler(std::unique_ptr<CommandDTO> shootCommand);

    virtual void execute(Game& game, std::atomic<bool>& keepRunning, double deltaTime);
};

#endif  // SHOOT_HANDLER_H_
