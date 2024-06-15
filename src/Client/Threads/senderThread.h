#ifndef CLIENT_SENDER_THREAD_H
#define CLIENT_SENDER_THREAD_H

#include <atomic>
#include <memory>
#include <vector>
#include <unordered_map>

#include <arpa/inet.h>

#include "../../Common/DTO/createGame.h"
#include "../../Common/DTO/dto.h"
#include "../../Common/DTO/startGame.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../../Common/thread.h"
#include "DTO/command.h"

class SenderThread: public Thread {
private:
    std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>>& queue;
    std::shared_ptr<Socket>& socket;
    std::atomic<bool>& was_closed;
    bool closed;
    std::unordered_map<char, bool> additionalData;

    void sendCommandDTO(const CommandDTO& cmd);
    void sendAditionalData(const CommandDTO& cmd);
public:
    SenderThread(std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>>& queue,
        std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed);
    void run() override;
    void sendCreateGame(const CommandDTO& cmd);
    void sendJoinGame(const CommandDTO& cmd);
    void sendStartGame(const CommandDTO& cmd);
    ~SenderThread();
};

#endif  // CLIENT_SENDER_THREAD_H
