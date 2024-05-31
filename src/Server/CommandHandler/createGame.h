#ifndef CREATE_GAME_HANDLER_H_
#define CREATE_GAME_HANDLER_H_

#include "../../Common/DTO/createGame.h"
#include "../../Common/DTO/lobby.h"

#include "command.h"

class CreateGameHandler: public CommandHandler {
private:
    std::unique_ptr<CreateGameDTO> command;

public:
    explicit CreateGameHandler(std::unique_ptr<CreateGameDTO> command);

    virtual std::unique_ptr<LobbyDTO> execute(
            GameMonitor& gameMonitor, std::atomic<bool>& inGame,
            std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue) = 0;
};

#endif  // CREATE_GAME_HANDLER_H_