#ifndef GAME_MONITOR_H_
#define GAME_MONITOR_H_

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "../../Common/Types/episode.h"
#include "../../Common/Types/gameMode.h"

#include "game.h"

class GameMonitor {
private:
    std::map<std::string, std::unique_ptr<Game>> games;
    std::mutex mtx;

public:
    GameMonitor();
    bool createGame(int32_t playerId, Episode episode, GameMode gameMode, uint8_t maxPlayers,
                    std::string gameName);
    void addPlayer(const std::string& gameName, Player&& player);
    void launchGame(const std::string& gameName);
    void listGames(std::string& list);
    void endGame(const std::string& gameName);
    void endAllGames();
};

#endif  // GAME_MONITOR_H_
