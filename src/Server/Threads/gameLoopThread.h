#ifndef GAMELOOP_THREAD_H_
#define GAMELOOP_THREAD_H_
#include <atomic>

#include "../../Common/Models/gameTypes.h"
#include "../../Common/queue.h"
#include "../../Common/thread.h"
#include "../Physics/gameStatus.h"
// #include "../Physics/physics.h"
#include <memory>
#include <string>

#include "../../Common/queueMonitor.h"


class GameLoopThread: public Thread {
private:
    std::shared_ptr<Queue<std::string>> sendQueue;
    std::shared_ptr<Queue<GameTypes::Action>> recvQueue;
    std::atomic<bool> running{true};
    // Physics physics;
    GameStatus& gameStatus;

public:
    GameLoopThread(std::shared_ptr<Queue<GameTypes::Action>> recvQueue,
                   std::shared_ptr<QueueMonitor<std::string>> QueueMonitor, GameStatus& gameStatus);
    void run() override;
    void stop() override;
};

#endif  // GAMELOOP_THREAD_H_
