#ifndef GAMELOOP_H_
#define GAMELOOP_H_
#include <atomic>

#include "../../Common/Models/gameStatus.h"
#include "../../Common/Models/gameTypes.h"
#include "../../Common/queue.h"
#include "../../Common/thread.h"
// #include "../Physics/physics.h"
#include "../Game/queueMonitor.h"

#include "broadcasterThread.h"

class GameLoop: public Thread {
private:
    std::shared_ptr<Queue<std::string>> sendQueue;
    std::shared_ptr<Queue<GameTypes::Action>> recvQueue;
    std::atomic<bool> running{true};
    // Physics physics;
    GameStatus& gameStatus;

public:
    GameLoop(std::shared_ptr<Queue<std::string>> sendQueue,
             std::shared_ptr<Queue<GameTypes::Action>> recvQueue, GameStatus& gameStatus);
    void run() override;
    void stop() override;
    ~GameLoop();
};

#endif  // GAMELOOP_H_
