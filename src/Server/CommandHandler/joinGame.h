#ifndef JOIN_GAME_HANDLER_H_
#define JOIN_GAME_HANDLER_H_

#include "../../Common/DTO/joinGame.h"
#include "../../Common/queue.h"

#include <memory>
#include "command.h"

class JoinGameHandler: public CommandHandler {
private:
    std::unique_ptr<JoinGameDTO> command;

public:
    explicit JoinGameHandler(std::unique_ptr<JoinGameDTO> command);

    virtual std::unique_ptr<LobbyDTO> execute(
            GameMonitor& gameMonitor, std::atomic<bool>& inGame,
            std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue);
};

#endif  // JOIN_GAME_HANDLER_H_
