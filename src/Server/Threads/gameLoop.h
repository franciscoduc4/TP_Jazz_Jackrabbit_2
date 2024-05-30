#ifndef GAMELOOP_THREAD_H_
#define GAMELOOP_THREAD_H_
#include <atomic>
#include <memory>
#include <string>

#include "../../Common/Models/gameTypes.h"
#include "../../Common/queue.h"
#include "../../Common/queueMonitor.h"
#include "../../Common/thread.h"
#include "../Physics/gameStatus.h"
#include "../Physics/physics.h"


class GameLoopThread: public Thread {
private:
    std::shared_ptr<Queue<GameTypes::Action>> recvQueue;
    std::atomic<bool> running{true};
    Physics physics;
    std::shared_ptr<GameStatus> gameStatus;
    std::shared_ptr<QueueMonitor<std::string>> queueMonitor;
    float frameTime = 0.016f;  // Assuming 60 FPS

    void broadcastGameState();
    void processActions();

    void handleMoveAction(const GameTypes::Action& action);
    void handleShootAction(const GameTypes::Action& action);
    void handleJumpAction(const GameTypes::Action& action);

public:
    GameLoopThread(std::shared_ptr<Queue<GameTypes::Action>> recvQueue,
                   std::shared_ptr<QueueMonitor<std::string>> QueueMonitor,
                   std::shared_ptr<GameStatus> gameStatus);
    void run() override;
    void stop() override;
};

#endif  // GAMELOOP_THREAD_H_
