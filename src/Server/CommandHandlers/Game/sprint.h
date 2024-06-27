#ifndef SPRINT_HANDLER_H_
#define SPRINT_HANDLER_H_

#include "../../../Common/DTO/gameCommand.h"

#include "gameCommand.h"

class SprintHandler: public GameCommandHandler {
private:
    std::unique_ptr<GameCommandDTO> sprintCommand;

public:
    explicit SprintHandler(std::unique_ptr<GameCommandDTO> sprintCommand);

    virtual void execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime);
};

#endif  // SPRINT_HANDLER_H_