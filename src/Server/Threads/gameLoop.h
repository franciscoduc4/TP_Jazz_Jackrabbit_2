#ifndef GAMELOOP_THREAD_H_
#define GAMELOOP_THREAD_H_
#include <atomic>
#include <memory>
#include <string>

#include "../../Common/DTO/game.h"
#include "../../Common/Types/episode.h"
#include "../../Common/Types/gameMode.h"
#include "../../Common/queue.h"
#include "../../Common/queueMonitor.h"
#include "../../Common/thread.h"
#include "../Game/game.h"


class GameLoopThread: public Thread {
private:
    double frameRate;
    Game game;
    QueueMonitor<std::unique_ptr<GameDTO>> queueMonitor;
    int32_t gameId;
    std::string gameName;
    bool exponentialIncrease = true;
    const size_t exponentialThreshold = 100;
    std::atomic<bool> keepRunning;
    std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue;
    uint8_t maxPlayers;
    uint8_t currentPlayers;
    size_t commandsToProcess;

public:
    GameLoopThread(int32_t gameId, std::string gameName, int32_t playerId, Episode episode,
                   GameMode gameMode, uint8_t maxPlayers, CharacterType characterType,
                   std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                   QueueMonitor<std::unique_ptr<GameDTO>>& queueMonitor);

    void run() override;
    void addPlayer(int32_t playerId, CharacterType characterType);
    bool deletePlayer(int32_t playerId);
    int32_t getGameId();
    std::string getGameName();
    void stop();
    bool isFull() const;
    void processCommands(double deltaTime);
    void adjustCommandsToProcess(std::chrono::duration<double> processingDuration,
                                 double frameRate);
                            
};

#endif  // GAMELOOP_THREAD_H_
