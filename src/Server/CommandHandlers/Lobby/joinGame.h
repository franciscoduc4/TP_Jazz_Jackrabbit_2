#ifndef JOIN_GAME_HANDLER_H_
#define JOIN_GAME_HANDLER_H_

#include <memory>

#include "../../../Common/DTO/joinGame.h"
#include "../../../Common/queue.h"
#include "../../../Common/DTO/dto.h"

#include "lobbyCommand.h"

class JoinGameHandler: public LobbyCommandHandler {
private:
    std::unique_ptr<JoinGameDTO> command;

public:
    explicit JoinGameHandler(std::unique_ptr<JoinGameDTO> command);

    virtual std::unique_ptr<CommandDTO> execute(
            GameMonitor& gameMonitor, std::atomic<bool>& inGame,
            std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
            std::shared_ptr<Queue<std::unique_ptr<GameDTO>>> sendQueue);
};

#endif  // JOIN_GAME_HANDLER_H_
