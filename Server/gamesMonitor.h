#ifndef GAMES_MONITOR_H_
#define GAMES_MONITOR_H_

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "game.h"
#include "playerHandler.h"

class GamesMonitor {
private:
    std::map<std::string, std::shared_ptr<Game>> games;
    std::mutex mtx;

public:
    GamesMonitor();
    void addPlayer(const std::string& gameName, std::shared_ptr<PlayerHandler> player);
    void removePlayer(const std::string& gameName, std::shared_ptr<PlayerHandler> player);
    void addGame(std::shared_ptr<Game> game);
    void removeGame(const std::string& gameName);
};


#endif  // GAMES_MONITOR_H_
