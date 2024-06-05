#include "gameMonitor.h"

#include <sstream>
#include <utility>

GameMonitor::GameMonitor(QueueMonitor<std::unique_ptr<GameDTO>>& queueMonitor):
        queueMonitor(queueMonitor) {}

bool GameMonitor::createGame(int32_t playerId, Episode episode, GameMode gameMode,
                             uint8_t maxPlayers, CharacterType characterType, std::string gameName,
                             std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                             int32_t gameId) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& [id, game]: games) {
        if (game->getGameName() == gameName) {
            return false;
        }
    }
    games[gameId] =
            std::make_unique<GameLoopThread>(gameId, gameName, playerId, episode, gameMode,
                                             maxPlayers, characterType, recvQueue, queueMonitor);

    return true;
}

bool GameMonitor::joinGame(int32_t playerId, int32_t gameId, CharacterType characterType) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(gameId);
    if (it != games.end()) {
        auto& [id, game] = *it;
        if (!game->isFull()) {
            game->addPlayer(playerId, characterType);
            return true;
        }
    }
    return false;
}

bool GameMonitor::startGame(int32_t playerId, int32_t gameId) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(gameId);
    if (it != games.end()) {
        auto& [id, game] = *it;
        if (game->isFull()) {
            game->start();
            return true;
        }
    }
    return false;
}

std::map<int32_t, std::string> GameMonitor::getGamesList() {
    std::lock_guard<std::mutex> lock(mtx);
    std::map<int32_t, std::string> list;
    for (auto& [id, game]: games) {
        list[id] = game->getGameName();
    }
    return list;
}

void GameMonitor::endGame(const std::string& gameName) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto it = games.begin(); it != games.end(); ++it) {
        if (it->second->getGameName() == gameName) {
            it->second->stop();
            it->second->join();
            games.erase(it);
            return;
        }
    }
}

void GameMonitor::endAllGames() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& [id, game]: games) {
        game->stop();
        game->join();
    }
    games.clear();
}