#include "gameLoop.h"

#include <chrono>


GameLoopThread::GameLoopThread(std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                               QueueMonitor<std::unique_ptr<GameDTO>>& queueMonitor,
                               GameMap& gameMap):
        frameRate(0.016),  // 1 frame per 16 ms === 60 fps
        keepRunning(true),
        commandsToProcess(1),
        recvQueue(recvQueue),
        queueMonitor(),
        gameMap(gameMap) {}

void GameLoopThread::run() {
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (keepRunning) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> deltaTime = currentTime - lastTime;

        processCommands(deltaTime.count());

        gameMap.update(deltaTime.count());

        std::unique_ptr<GameDTO> gameDTO = gameMap.getGameDTO();
        queueMonitor.broadcast(std::move(gameDTO));

        auto processingEndTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> processingDuration = processingEndTime - currentTime;

        adjustCommandsToProcess(processingDuration, frameRate);

        std::chrono::duration<double> frameDuration(frameRate);
        auto sleepTime = frameDuration - processingDuration;
        if (sleepTime > std::chrono::duration<double>(0)) {
            std::this_thread::sleep_for(sleepTime);
        }

        lastTime = std::chrono::high_resolution_clock::now();
    }
}

void GameLoopThread::processCommands(double deltaTime) {
    size_t processedCommands = 0;
    for (size_t i = 0; i < commandsToProcess; ++i) {
        std::unique_ptr<CommandDTO> command;
        if (recvQueue->try_pop(command)) {
            std::unique_ptr<GameCommandHandler> handler =
                    GameCommandHandler::createHandler(std::move(command));
            handler->execute(gameMap, keepRunning, deltaTime);
            processedCommands++;
        } else {
            break;
        }
    }
}

void GameLoopThread::adjustCommandsToProcess(std::chrono::duration<double> processingDuration,
                                             double frameRate) {
    if (processingDuration.count() < frameRate) {
        if (exponentialIncrease) {
            commandsToProcess *= 2;
            if (commandsToProcess >= exponentialThreshold) {
                exponentialIncrease = false;
            }
        } else {
            commandsToProcess++;
        }
    } else if (processingDuration.count() > frameRate) {
        commandsToProcess /= 2;
        if (commandsToProcess < exponentialThreshold) {
            exponentialIncrease = true;
        }
    }
    commandsToProcess = std::max(size_t(1), commandsToProcess);
}


void GameLoopThread::stop() { keepRunning = false; }
