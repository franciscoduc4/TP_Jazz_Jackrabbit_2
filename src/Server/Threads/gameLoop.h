#ifndef GAMELOOP_THREAD_H_
#define GAMELOOP_THREAD_H_
#include <atomic>
#include <memory>
#include <string>

#include "../../Common/DTO/command.h"
#include "../../Common/DTO/game.h"
#include "../../Common/Types/gameInfo.h"
#include "../../Common/Types/gameMode.h"
#include "../../Common/queue.h"
#include "../../Common/queueMonitor.h"
#include "../../Common/thread.h"
#include "../CommandHandlers/Game/gameCommand.h"
#include "../Game/gameMap.h"


class GameLoopThread: public Thread {
private:
    double frameRate;
    bool exponentialIncrease = true;
    const size_t exponentialThreshold = 16;
    std::atomic<bool> keepRunning;
    size_t commandsToProcess;
    std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue;
    QueueMonitor& queueMonitor;
    GameMap& gameMap;
    uint8_t gameId;

public:
    GameLoopThread(const std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>>& recvQueue,
                   QueueMonitor& queueMonitor, GameMap& gameMap,
                   uint8_t gameId);

    void run() override;
    void stop();
    void processCommands(double deltaTime);
    void adjustCommandsToProcess(std::chrono::duration<double> processingDuration,
                                 double frameRate);

    bool isRunning() const;
};

#endif  // GAMELOOP_THREAD_H_
