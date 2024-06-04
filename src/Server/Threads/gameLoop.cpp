#include "gameLoop.h"

#include <chrono>


GameLoopThread::GameLoopThread(int32_t gameId, std::string gameName, int32_t playerId,
                               Episode episode, GameMode gameMode, uint8_t maxPlayers,
                               CharacterType characterType,
                               std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                               QueueMonitor<std::unique_ptr<GameDTO>>& queueMonitor):
        frameRate(0.016),  // 1 frame per 16 ms === 60 fps
        game({100, 100}),  // config del YAML
        queueMonitor(),
        gameId(gameId),
        gameName(gameName),
        keepRunning(true),
        recvQueue(recvQueue),
        maxPlayers(maxPlayers),
        currentPlayers(1),
        commandsToProcess(1) {
    game.addCharacter(playerId, characterType);
}

void GameLoopThread::run() {
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (keepRunning) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> deltaTime = currentTime - lastTime;

        processCommands(deltaTime.count());

        game.update(deltaTime.count());

        std::unique_ptr<GameDTO> gameDTO = game.getGameDTO();
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
            game.handleCommand(std::move(command), keepRunning, deltaTime);
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

std::string GameLoopThread::getGameName() { return gameName; }

int32_t GameLoopThread::getGameId() { return gameId; }

void GameLoopThread::addPlayer(int32_t playerId, CharacterType characterType) {
    currentPlayers++;
    game.addCharacter(playerId, characterType);
}

bool GameLoopThread::isFull() const { return currentPlayers == maxPlayers; }

void GameLoopThread::stop() { keepRunning = false; }

bool GameLoopThread::deletePlayer(int32_t playerId) {
    if (game.removeCharacter(playerId)) {
        currentPlayers--;
        return true;
    }
    return false;
}