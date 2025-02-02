#include "gameLoop.h"

#include <algorithm>
#include <chrono>
#include <thread>

#include "printer.h"

GameLoopThread::GameLoopThread(const std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>>& recvQueue,
                               QueueMonitor& queueMonitor, GameMap& gameMap, uint8_t gameId):
        frameRate(ServerConfig::getGameFrameRate()),
        keepRunning(false),
        commandsToProcess(ServerConfig::getGameCommandsToProcess()),
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
        keepRunning.store(true);
        auto lastTime = std::chrono::high_resolution_clock::now();

        auto gameDTO = gameMap.getGameDTO();
        queueMonitor.broadcast(gameId, std::move(gameDTO));
        std::cout << "[GAME LOOP] Initial game state broadcasted" << std::endl;

        while (keepRunning) {
            auto currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            // std::cout << "[GAME LOOP] Processing commands, deltaTime: " << deltaTime.count()
            //   << std::endl;
            processCommands(deltaTime.count());

            // std::cout << "[GAME LOOP] Updating game map, deltaTime: " << deltaTime.count()
            //   << std::endl;
            gameMap.update(deltaTime.count());

            std::unique_ptr<GameDTO> gameDTO = gameMap.getGameDTO();
            queueMonitor.broadcast(gameId, std::move(gameDTO));
            // std::cout << "[GAME LOOP] Game state broadcasted" << std::endl;

            if (!keepRunning.load()) {
                this->recvQueue->close();
            }
            auto processingEndTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> processingDuration = processingEndTime - currentTime;
            // std::cout << "[GAME LOOP] Processing duration: " << processingDuration.count()
            //   << std::endl;

            auto sleepTime = std::chrono::duration<float>(frameRate) - processingDuration;
            if (sleepTime.count() > 0) {
                // std::cout << "[GAME LOOP] Sleeping for: " << sleepTime.count() << " seconds"
                //   << std::endl;
                std::this_thread::sleep_for(sleepTime);
            }
        }
        std::cout << "[GAME LOOP] Game loop stopped" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[GAME LOOP] Error in game loop: " << e.what() << std::endl;
    }
}

void GameLoopThread::processCommands(float deltaTime) {
    try {
        size_t processedCommands = 0;
        size_t maxCommandsPerFrame = ServerConfig::getGameCommandsToProcess() * 2;

        while (processedCommands < maxCommandsPerFrame) {
            std::unique_ptr<CommandDTO> command;
            if (recvQueue->try_pop(command)) {
                if (!command) {
                    Printer::printWarningHighlightedMessage("[GAME LOOP] Null command received");
                    continue;
                }

                auto handler = GameCommandHandler::createHandler(std::move(command));
                if (!handler) {
                    Printer::printErrorHighlightedMessage("[GAME LOOP] Invalid command received");
                    continue;
                }
                handler->execute(gameMap, keepRunning, deltaTime);

                processedCommands++;
            } else {
                Printer::printErrorHighlightedMessage("[GAME LOOP] No more commands to process");
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[GAME LOOP] Error processing commands: " << e.what() << std::endl;
    }
}

void GameLoopThread::stop() {
    keepRunning.store(false);
    std::cout << "[GAME LOOP] Stop called, setting keepRunning to false" << std::endl;
}

bool GameLoopThread::isRunning() const {
    std::cout << "[GAME LOOP] isRunning called, returning: " << keepRunning.load() << std::endl;
    return keepRunning.load();
}
