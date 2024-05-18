#ifndef GAME_H_
#define GAME_H_

#include <map>
#include <vector>
#include "../Common/queue.h"
#include "../Common/thread.h"
#include "../Threads/broadcasterThread.h"
#include <memory>
#include <string>
#include "gameLoop.h"
#include "gameMonitor.h"
#include "player.h"
#include "queueMonitor.h"

class Game {

    private:
        std::string name;
        int maxPlayers;
        int currentPlayers;
        GameLoop gameLoop;
        Queue<GameTypes::Action> recvQueue;
        std::vector<Player> players;
        std::map<int, std::shared_ptr<ReceiverThread>> receiverThreads;
        BroadcasterThread broadcaster;
        bool running;

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
