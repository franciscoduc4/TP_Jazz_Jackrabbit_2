#include "gameMonitor.h"

#include <sstream>
#include <utility>

GameMonitor::GameMonitor() {}

bool GameMonitor::createGame(int32_t playerId, Episode episode, GameMode gameMode,
                             uint8_t maxPlayers, std::string gameName,
                             std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue) {
    std::lock_guard<std::mutex> lock(mtx);

    for (auto& game: games) {
        if (game.getGameName() == gameName) {
            return false;
        }
    }
    int32_t gameId = games.size();
    games.emplace_back(playerId, episode, gameMode, maxPlayers, gameName, recvQueue, gameId);
    return true;
}

bool GameMonitor::joinGame(int32_t playerId, int32_t gameId) {
    std::lock_guard<std::mutex> lock(mtx);

    for (auto& game: games) {
        if (game.getGameId() == gameId && !game.isFull()) {
            game.addPlayer(playerId);
            return true;
        }
    }
    return false;
}

bool GameMonitor::startGame(int32_t playerId, int32_t gameId) {
    std::lock_guard<std::mutex> lock(mtx);

    for (auto& game: games) {
        if (game.getGameId() == gameId && game.isFull()) {
            game.start();
            return true;
        }
    }
    return false;
}

std::map<int32_t, std::string> GameMonitor::getGamesList() {
    std::lock_guard<std::mutex> lock(mtx);
    std::map<int32_t, std::string> list;
    for (auto& game: games) {
        list[game.getGameId()] = game.getGameName();
    }
    return list;
}
