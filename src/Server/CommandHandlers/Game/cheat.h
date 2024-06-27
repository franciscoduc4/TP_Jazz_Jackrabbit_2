#ifndef CHEAT_HANDLER_H
#define CHEAT_HANDLER_H

#include <atomic>

#include "DTO/gameCommand.h"

#include "gameCommand.h"


class CheatHandler : public GameCommandHandler {
private:
    std::unique_ptr<CommandDTO> command;
public:
    explicit CheatHandler(std::unique_ptr<CommandDTO> command);

    virtual void execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime);
};


#endif  // CHEAT_HANDLER_H
