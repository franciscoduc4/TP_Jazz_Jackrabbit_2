#ifndef SERVER_PLAYER_HANDLER_H_
#define SERVER_PLAYER_HANDLER_H_

#include <atomic>
#include <memory>
#include "../Common/queue.h"

class PlayerHandler { 
    private:
        std::atomic<bool> playerIsAlive{true};
        Protocol protocol;
        GameMonitor& gameMonitor;
        Queue<Action>& actionQueue;
        Receiver receiver;
        Sender sender;
        std::shared_ptr<Queue<Action>>& gameQueue;

    public: 
        PlayerHandler(Socket&& playerSocket, GameMonitor& gameMonitor, 
        std::shared_ptr<Queue<Action>>& actionQueue);
        void run();
        void stop();
        void join();
        bool isAlive();
}

#endif // SERVER_PLAYER_HANDLER_H_
