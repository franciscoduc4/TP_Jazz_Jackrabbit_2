#ifndef START_GAME_HANDLER_H_
#define START_GAME_HANDLER_H_

#include <memory>

#include "../../../Common/DTO/startGame.h"
#include "../../../Common/DTO/dto.h"
#include "../../../Common/queue.h"

#include "lobbyCommand.h"

class StartGameHandler: public LobbyCommandHandler {
private:
    std::unique_ptr<StartGameDTO> command;

public:
    explicit StartGameHandler(std::unique_ptr<StartGameDTO> command);

    virtual std::unique_ptr<CommandDTO> execute(
            GameMonitor& gameMonitor, std::atomic<bool>& inGame,
            std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
            std::shared_ptr<Queue<std::unique_ptr<GameDTO>>> sendQueue);
};

#endif  // START_GAME_HANDLER_H_
