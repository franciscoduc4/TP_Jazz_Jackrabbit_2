#ifndef GAME_H_
#define GAME_H_

#include <vector>

#include "../Common/thread.h"

#include "gameLoop.h"
#include "gamesMonitor.h"
#include "playerHandler.h"

class Game {
private:
    std::string name;
    int maxPlayers;
    int currentPlayers;
    GameLoop gameLoop;
    std::vector<std::shared_ptr<PlayerHandler>> players;
    bool running;

public:
    Game(std::string name, int maxPlayers);
    void addPlayer(std::shared_ptr<PlayerHandler> player);
    void removePlayer(std::shared_ptr<PlayerHandler> player);
    void launch();
    void stop();
    bool isRunning() const;
    bool isFull() const;
    std::string getName() const;
    int getMaxPlayers() const;
    int getCurrentPlayers() const;
    ~Game();
};

#endif  // GAME_H_
