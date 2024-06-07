#ifndef MOVE_HANDLER_H_
#define MOVE_HANDLER_H_

#include "../../../Common/DTO/move.h"

#include "gameCommand.h"

class MoveHandler: public GameCommandHandler {
private:
    std::unique_ptr<MoveDTO> moveCommand;

public:
    explicit MoveHandler(std::unique_ptr<MoveDTO> moveCommand);

    virtual void execute(GameMap& gameMap, std::atomic<bool>& keepRunning, double deltaTime);
};

#endif  // MOVE_HANDLER_H_