#include "gameLoopThread.h"
#include <iostream>

GameLoop::GameLoop(BroadcasterThread& broadcasterThread, 
Queue<GameTypes::Action>& recvQueue, GameStatus& gameStatus)
    : 
    broadcasterThread(broadcasterThread), 
    recvQueue(recvQueue),
    physics(),
    gameStatus(gameStatus) {}

void GameLoop::run() {

    try {
        
        while (running) {
            auto startTime = std::chrono::high_resolution_clock::now();

            GameTypes::Action action;
            if (recvQueue.try_pop(action)) {
                //llamar a las fisicas dependiendo la accion

            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in GameLoop: " << e.what() << std::endl;
    }

}
