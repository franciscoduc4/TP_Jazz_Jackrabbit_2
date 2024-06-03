#ifndef GAME_MONITOR_H_
#define GAME_MONITOR_H_

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "../../Common/Types/episode.h"
#include "../../Common/Types/gameMode.h"
#include "../../Common/queueMonitor.h"
#include "../Threads/gameLoop.h"

class GameMonitor {
private:
    std::map<int32_t, std::unique_ptr<GameLoopThread>> games;
    std::mutex mtx;
    QueueMonitor<std::unique_ptr<GameDTO>>& queueMonitor;

public:
    explicit GameMonitor(QueueMonitor<std::unique_ptr<GameDTO>>& queueMonitor);
    bool createGame(int32_t playerId, Episode episode, GameMode gameMode, uint8_t maxPlayers,
                    CharacterType characterType, std::string gameName,
                    std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue, int32_t gameId);
    std::map<int32_t, std::string> getGamesList();
    bool joinGame(int32_t playerId, int32_t gameId, CharacterType characterType);
    bool startGame(int32_t playerId, int32_t gameId);
    void endGame(const std::string& gameName);
    void endAllGames();
};

#endif  // GAME_MONITOR_H_
