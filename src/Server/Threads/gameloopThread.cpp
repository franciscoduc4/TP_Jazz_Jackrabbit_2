#include "gameLoopThread.h"

#include <iostream>

GameLoopThread::GameLoopThread(std::shared_ptr<Queue<GameTypes::Action>> recvQueue,
                               std::shared_ptr<QueueMonitor<std::string>> queueMonitor,
                               std::shared_ptr<GameStatus> gameStatus):
        recvQueue(recvQueue), physics(), gameStatus(gameStatus), queueMonitor(queueMonitor) {}

void GameLoopThread::run() {
    try {
        while (running) {
            processActions();
            physics.update(gameStatus, frameTime);
            broadcastGameState();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in GameLoopThread: " << e.what() << std::endl;
    }
}

void GameLoopThread::stop() { _keep_running = false; }

void GameLoopThread::processActions() {
    GameTypes::Action action;
    while (recvQueue->try_pop(action)) {
        switch (action.type) {
            case GameTypes::ActionType::MOVE:
                handleMoveAction(action);
                break;
            case GameTypes::ActionType::SHOOT:
                handleShootAction(action);
                break;
            case GameTypes::ActionType::JUMP:
                handleJumpAction(action);
                break;
            default:
                break;
        }
    }
}

void GameLoopThread::handleMoveAction(const GameTypes::Action& action) {
    auto player = gameStatus->getCharacter(action.playerId);
    if (player) {
        player->move(action.direction);
    }
}

void GameLoopThread::handleShootAction(const GameTypes::Action& action) {
    auto player = gameStatus->getCharacter(action.playerId);
    if (player) {
        auto projectile = player->shoot(action.currentTime, action.shootDirection);
        if (projectile) {
            gameStatus->addProjectile(std::move(projectile));
        }
    }
}

void GameLoopThread::handleJumpAction(const GameTypes::Action& action) {
    auto player = gameStatus->getCharacter(action.playerId);
    if (player) {
        player->jump();
    }
}

void GameLoopThread::broadcastGameState() {
    std::string gameState = gameStatus->serialize();
    queueMonitor->broadcast(gameState);
}
