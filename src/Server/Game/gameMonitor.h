#ifndef GAME_MONITOR_H_
#define GAME_MONITOR_H_

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "../../Common/Types/episode.h"
#include "../../Common/Types/gameInfo.h"
#include "../../Common/Types/gameMode.h"
#include "../../Common/queueMonitor.h"
#include "../Game/game.h"

class GameMonitor {
private:
    std::map<uint32_t, std::unique_ptr<Game>> games;
    std::mutex mtx;
    QueueMonitor<std::unique_ptr<GameDTO>>& queueMonitor;

public:
    explicit GameMonitor(QueueMonitor<std::unique_ptr<GameDTO>>& queueMonitor);
    bool createGame(uint32_t playerId, Episode episode, GameMode gameMode, uint8_t maxPlayers,
                    CharacterType characterType, std::string gameName,
                    std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue, uint32_t gameId);
    std::map<uint32_t, GameInfo> getGamesList();
    bool joinGame(uint32_t playerId, uint32_t gameId, CharacterType characterType);
    bool startGame(uint32_t playerId, uint32_t gameId);
    // void broadcastToGame(uint32_t gameId, std::unique_ptr<CommandDTO> command);
    uint8_t getCurrentPlayers(uint32_t gameId);
    void endGame(const std::string& gameName);
    void endAllGames();
};

#endif  // GAME_MONITOR_H_
