#ifndef GAME_MONITOR_H_
#define GAME_MONITOR_H_

#include <map>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <string>

#include "../../Common/DTO/createGame.h"
#include "../../Common/Types/gameInfo.h"
#include "../../Common/Types/gameMode.h"
#include "../../Common/queueMonitor.h"
#include "maps/mapsManager.h"

#include "game.h"

class GameMonitor {
private:
    std::map<uint32_t, std::unique_ptr<Game>> games;
    std::mutex mtx;
    QueueMonitor<std::unique_ptr<DTO>>& queueMonitor;
    uint32_t gamesListSize = 0;

public:
    explicit GameMonitor(QueueMonitor<std::unique_ptr<DTO>>& queueMonitor);
    void createGame(uint32_t playerId, uint32_t mapId, GameMode gameMode, uint8_t maxPlayers,
                    CharacterType characterType, std::string gameName,
                    std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                    std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue);

    void joinGame(uint32_t playerId, uint32_t gameId, CharacterType characterType,
                  std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue);

    void startGame(uint32_t playerId, uint32_t gameId,
                   std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue);

    void gamesList(std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue);

    void mapsList(std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue);

    uint8_t getCurrentPlayers(uint32_t gameId);

    void endGame(const std::string& gameName);

    void endAllGames();
    uint32_t getGamesListSize();
};

#endif  // GAME_MONITOR_H_
