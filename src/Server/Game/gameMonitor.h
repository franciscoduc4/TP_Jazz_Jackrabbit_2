#ifndef GAME_MONITOR_H_
#define GAME_MONITOR_H_

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "../../Common/Types/episode.h"
#include "../../Common/Types/gameMode.h"

//#include "game.h"

class GameMonitor {
private:
    //std::map<int32_t, std::string> games;
    std::mutex mtx;

public:
    GameMonitor();
    bool createGame(int32_t playerId, Episode episode, GameMode gameMode, uint8_t maxPlayers,
                    std::string gameName);
    //void addPlayer(const std::string& gameName, Player&& player);
    void launchGame(const std::string& gameName);
    std::map<int32_t, std::string> listGames();
    bool joinGame(int32_t playerId, int32_t gameId);
    bool startGame(int32_t playerId, int32_t gameId);
    void endGame(const std::string& gameName);
    void endAllGames();
};

#endif  // GAME_MONITOR_H_
