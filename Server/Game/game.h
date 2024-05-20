#ifndef GAME_H_
#define GAME_H_

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "../../Common/queue.h"
#include "../../Common/thread.h"
#include "../Threads/broadcasterThread.h"
#include "../Threads/gameLoopThread.h"
#include "gameMonitor.h"
#include "player.h"
#include "queueMonitor.h"
#include "../../Common/gameStatus.h"  

class Game {
private:
    std::string name;
    int maxPlayers;
    int currentPlayers;
    Queue<GameTypes::Action> recvQueue;
    std::vector<Player> players;
    std::map<int, std::shared_ptr<ReceiverThread>> receiverThreads;
    BroadcasterThread broadcaster;
    bool running;
    GameLoop gameLoop;
    std::unique_ptr<GameStatus> gameStatus;  

public:
    Game(std::string name, int maxPlayers, Player&& firstPlayer);
    void addPlayer(Player&& player);
    void removePlayer(int playerId);
    void initPlayerThreads(Player& player);
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
