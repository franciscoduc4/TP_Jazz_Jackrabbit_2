#ifndef CREATE_GAME_HANDLER_H_
#define CREATE_GAME_HANDLER_H_

#include <memory>

#include "../../../Common/DTO/createGame.h"
#include "../../../Common/DTO/lobby.h"
#include "../../../Common/queue.h"
#include "../../../Common/DTO/dto.h"

#include "lobbyCommand.h"

class CreateGameHandler: public LobbyCommandHandler {
private:
    std::unique_ptr<CreateGameDTO> command;

public:
    explicit CreateGameHandler(std::unique_ptr<CreateGameDTO> command);

    virtual std::unique_ptr<CommandDTO> execute(
            GameMonitor& gameMonitor, std::atomic<bool>& inGame,
            std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
            std::shared_ptr<Queue<std::unique_ptr<GameDTO>>> sendQueue);
};

#endif  // CREATE_GAME_HANDLER_H_
