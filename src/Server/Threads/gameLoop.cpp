#include "gameLoop.h"

#include <chrono>

#include "../CommandHandlers/Game/gameCommand.h"

GameLoopThread::GameLoopThread(int32_t gameId, std::string gameName, int32_t& playerId,
                               Episode episode, GameMode gameMode, uint8_t maxPlayers,
                               CharacterType characterType,
                               std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                               QueueMonitor<std::unique_ptr<GameDTO>>& queueMonitor):
        frameRate(0.05),  // 1 frame per 50 ms === 20 fps
        game(),
        queueMonitor(),
        gameId(gameId),
        gameName(gameName),
        keepRunning(true),
        recvQueue(recvQueue),
        maxPlayers(maxPlayers),
        currentPlayers(1) {
    game.addCharacter(playerId, characterType);
}

void GameLoopThread::run() {
    auto lastTime = std::chrono::high_resolution_clock::now();
    while (keepRunning) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> deltaTime = currentTime - lastTime;

        // Procesamos los comandos
        std::unique_ptr<CommandDTO> command;
        recvQueue->try_pop(command);
        std::unique_ptr<GameCommandHandler> handler =
                GameCommandHandler::createHandler(std::move(command));
        handler->execute(game, keepRunning, deltaTime.count());
        // game.update(deltaTime.count());
        std::unique_ptr<GameDTO> gameDTO = game.getGameDTO();
        queueMonitor.broadcast(gameDTO);

        // Maintain a consistent frame rate
        std::chrono::duration<double> frameDuration(frameRate);
        auto sleepTime = frameDuration - deltaTime;
        if (sleepTime > std::chrono::duration<double>(0)) {
            std::this_thread::sleep_for(sleepTime);
        }

        lastTime = std::chrono::high_resolution_clock::now();
    }
}

std::string GameLoopThread::getGameName() { return gameName; }

int32_t GameLoopThread::getGameId() { return gameId; }

void GameLoopThread::addPlayer(int32_t playerId, CharacterType characterType) {
    currentPlayers++;
    game.addCharacter(playerId, characterType);
}

bool GameLoopThread::isFull() const { return currentPlayers == maxPlayers; }