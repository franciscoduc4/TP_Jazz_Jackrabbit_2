#ifndef GAMELOOP_H_
#define GAMELOOP_H_
#include <atomic>
#include "../../Common/thread.h"
#include "../../Common/queue.h"
#include "../../Common/gameTypes.h"
#include "broadcasterThread.h"
#include "../Physics/physics.h"
#include "../Game/gameStatus.h"

class GameLoop : public Thread {

private:
    BroadcasterThread& broadcasterThread;
    Queue<GameTypes::Action>& recvQueue;
    std::atomic<bool> running{true};
    Physics physics;
    GameStatus gameStatus;

public:
    GameLoop(BroadcasterThread& broadcasterThread, 
        Queue<GameTypes::Action>& recvQueue, GameStatus& gameStatus);
    void run() override;
    void stop() override;
    ~GameLoop();
};

#endif  // GAMELOOP_H_
