#include "gameLoopThread.h"

#include <iostream>

GameLoop::GameLoop(std::shared_ptr<Queue<std::string>> sendQueue,
                   std::shared_ptr<Queue<GameTypes::Action>> recvQueue, GameStatus& gameStatus):
        sendQueue(sendQueue), recvQueue(recvQueue), gameStatus(gameStatus) {}

void GameLoop::run() {

    try {

        while (running) {
            auto startTime = std::chrono::high_resolution_clock::now();

            GameTypes::Action action;
            if (recvQueue->try_pop(action)) {
                // llamar a las fisicas dependiendo la accion
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in GameLoop: " << e.what() << std::endl;
    }
}
