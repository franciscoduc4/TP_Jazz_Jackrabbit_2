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
#include "../../Common/Config/ServerConfig.h"

class GameLoopThread: public Thread {
private:
    float frameRate;
    std::atomic<bool> keepRunning;
    uint32_t commandsToProcess;
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
    void processCommands(float deltaTime);
    bool isRunning() const;
};

#endif  // GAMELOOP_THREAD_H_
