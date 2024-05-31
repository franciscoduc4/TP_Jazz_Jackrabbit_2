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
#include "../../Common/DTO/game.h"
#include "../../Common/Types/episode.h"
#include "../../Common/Types/gameMode.h"


class GameLoopThread: public Thread {
    private:
        Physics physics;
        QueueMonitor<GameDTO> queueMonitor;
        int32_t gameId;
        std::string gameName;
        std::atomic<bool> keepRunning;
        std::shared_ptr<Queue<CommandDTO>> recvQueue;
        uint8_t maxPlayers;
        bool isFull;
    public:
        GameLoopThread(int32_t gameId, std::string gameName, 
        int32_t& playerId, Episode episode, GameMode gameMode,
        uint8_t maxPlayers, std::shared_ptr<Queue<GameDTO>> sendQueue);

        void run() override;
        void addPlayer(int32_t playerId, std::shared_ptr<Queue<GameDTO>> sendQueue);
        bool deletePlayer(int32_t playerId);
        int32_t getGameId();
        std::string getGameName();
        void stop();

};

#endif  // GAMELOOP_THREAD_H_
