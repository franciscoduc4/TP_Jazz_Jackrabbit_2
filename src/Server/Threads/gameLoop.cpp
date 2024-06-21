#include "gameLoop.h"
#include <chrono>
#include <thread>
#include <algorithm>

GameLoopThread::GameLoopThread(std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                               QueueMonitor& queueMonitor, GameMap& gameMap,
                               uint8_t gameId)
        : frameRate(0.016),  // 1 frame per 16 ms === 60 fps
          keepRunning(false),
          recvQueue(recvQueue),
          queueMonitor(queueMonitor),
          gameMap(gameMap),
          gameId(gameId) {
    std::cout << "[GAME LOOP] GameLoopThread initialized with gameId: " << static_cast<int>(gameId)
              << std::endl;
}

void GameLoopThread::run() {
    try {
        std::cout << "[GAME LOOP] Game loop started" << std::endl;
        keepRunning = true;
        auto lastTime = std::chrono::high_resolution_clock::now();

        auto gameDTO = gameMap.getGameDTO();
        queueMonitor.broadcast(gameId, std::move(gameDTO));
        std::cout << "[GAME LOOP] Initial game state broadcasted" << std::endl;

        while (keepRunning) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            std::cout << "[GAME LOOP] Processing commands, deltaTime: " << deltaTime.count()
                      << std::endl;
            processCommands(deltaTime.count());

            std::cout << "[GAME LOOP] Updating game map, deltaTime: " << deltaTime.count()
                      << std::endl;
            gameMap.update(deltaTime.count());

            std::unique_ptr<GameDTO> gameDTO = gameMap.getGameDTO();
            queueMonitor.broadcast(gameId, std::move(gameDTO));
            std::cout << "[GAME LOOP] Game state broadcasted" << std::endl;

            auto processingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> processingDuration = processingEndTime - currentTime;
            std::cout << "[GAME LOOP] Processing duration: " << processingDuration.count()
                      << std::endl;

            // Sleep only if necessary to maintain the frame rate
            auto sleepTime = std::chrono::duration<double>(frameRate) - processingDuration;
            if (sleepTime.count() > 0) {
                std::cout << "[GAME LOOP] Sleeping for: " << sleepTime.count() << " seconds"
                          << std::endl;
                std::this_thread::sleep_for(sleepTime);
            }
        }
        std::cout << "[GAME LOOP] Game loop stopped" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[GAME LOOP] Error in game loop: " << e.what() << std::endl;
    }
}

void GameLoopThread::processCommands(double deltaTime) {
    try {
        size_t processedCommands = 0;
        size_t maxCommandsPerFrame = 10; // Limit the number of commands processed per frame

        while (processedCommands < maxCommandsPerFrame) {
            std::unique_ptr<CommandDTO> command;
            if (recvQueue->try_pop(command)) {
                std::cout << "[GAME LOOP] Processing command" << std::endl;
                if (!command) {
                    std::cerr << "[GAME LOOP] Null command received" << std::endl;
                    continue;
                }

                auto handler = GameCommandHandler::createHandler(std::move(command));
                if (!handler) {
                    std::cerr << "[GAME LOOP] Failed to create handler" << std::endl;
                    continue;
                }

                std::cout << "[GAME LOOP] Executing handler" << std::endl;
                handler->execute(gameMap, keepRunning, deltaTime);

                processedCommands++;
                std::cout << "[GAME LOOP] Command processed number: " << processedCommands
                          << std::endl;
            } else {
                std::cout << "[GAME LOOP] No more commands to process" << std::endl;
                break;
            }
        }
        std::cout << "[GAME LOOP] Processed " << processedCommands << " commands" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[GAME LOOP] Error processing commands: " << e.what() << std::endl;
    }
}

void GameLoopThread::stop() {
    keepRunning = false;
    std::cout << "[GAME LOOP] Stop called, setting keepRunning to false" << std::endl;
}

bool GameLoopThread::isRunning() const {
    std::cout << "[GAME LOOP] isRunning called, returning: " << keepRunning << std::endl;
    return keepRunning;
}
