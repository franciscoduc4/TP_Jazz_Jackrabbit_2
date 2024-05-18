#ifndef GAME_MONITOR_H_
#define GAME_MONITOR_H_

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "game.h"
#include "player.h"

class GameMonitor {
private:
    std::map<std::string, Game> games;
    std::mutex mtx;

public:
    GameMonitor();
    void createGame(const std::string& gameName, int maxPlayers, Player&& player);
    void addPlayer(const std::string& gameName, Player&& player);
    void launchGame(const std::string& gameName);
    std::string listGames();
    void endGame(const std::string& gameName);
    void endAllGames();
};

#endif  // GAME_MONITOR_H_
