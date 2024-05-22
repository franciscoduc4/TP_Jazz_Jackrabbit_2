#ifndef GAME_H_
#define GAME_H_

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../Physics/gameStatus.h"
#include "../../Common/queue.h"
#include "../../Common/thread.h"
#include "../Threads/broadcasterThread.h"
#include "../Threads/gameLoopThread.h"

#include "player.h"
#include "queueMonitor.h"

class Game {
private:
    std::string name;
    int maxPlayers;
    int currentPlayers;
    std::shared_ptr<Queue<GameTypes::Action>> recvQueue;
    std::shared_ptr<Queue<std::string>> sendQueue;
    std::shared_ptr<QueueMonitor<std::string>> queueMonitor;
    std::vector<Player> players;
    std::map<int, std::unique_ptr<ReceiverThread>> receiverThreads;
    std::map<int, std::unique_ptr<SenderThread>> senderThreads;
    BroadcasterThread broadcaster;
    bool running;
    GameLoopThread gameLoop;
    GameStatus gameStatus;

public:
    Game() = default;

    Game(const std::string& name, int maxPlayers, Player&& firstPlayer);
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
