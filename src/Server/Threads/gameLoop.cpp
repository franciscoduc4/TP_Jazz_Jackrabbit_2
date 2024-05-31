#include "gameLoop.h"

GameLoopThread::GameLoopThread(int32_t gameId, std::string gameName, int32_t& playerId,
                               Episode episode, GameMode gameMode, uint8_t maxPlayers,
                               std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue):
        // physics(episode, gameMode),
        queueMonitor(),
        gameId(gameId),
        gameName(gameName),
        keepRunning(true),
        recvQueue(recvQueue),
        maxPlayers(maxPlayers),
        currentPlayers(1) {}

void GameLoopThread::run() {}

std::string GameLoopThread::getGameName() { return gameName; }

int32_t GameLoopThread::getGameId() { return gameId; }

void GameLoopThread::addPlayer(int32_t playerId) { currentPlayers++; }

bool GameLoopThread::isFull() const { return currentPlayers == maxPlayers; }