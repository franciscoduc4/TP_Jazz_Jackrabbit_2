#ifndef GAME_COMMAND_HANDLER_H_
#define GAME_COMMAND_HANDLER_H_

#include <memory>

#include "../../../Common/DTO/command.h"
#include "../../../Common/DTO/game.h"
#include "../../../Common/Types/command.h"
#include "../../../Common/queue.h"
#include "../../Game/game.h"

class Game;

class GameCommandHandler {
public:
    virtual void execute(Game& game, std::atomic<bool>& keepRunning, double deltaTime) = 0;
    static std::unique_ptr<GameCommandHandler> createHandler(std::unique_ptr<CommandDTO> command);
};

#endif  // GAME_COMMAND_HANDLER_H_
