#include "gameMonitor.h"

#include <sstream>
#include <utility>

GameMonitor::GameMonitor() {}

bool GameMonitor::createGame(int32_t playerId, Episode episode, GameMode gameMode,
                             uint8_t maxPlayers, std::string gameName) {
    //std::lock_guard<std::mutex> lock(mtx);
    // games[episode] = std::make_unique<Game>(episode, maxPlayers, std::move(player));
    // if (games.find(gameName) != games.end()) {
    //     return false;
    // }
    return true;
}

// void GameMonitor::addPlayer(const std::string& gameName, Player&& player) {
//     std::lock_guard<std::mutex> lock(mtx);
//     auto it = games.find(gameName);
//     if (it != games.end()) {
//         it->second->addPlayer(std::move(player));
//     }
// }

void GameMonitor::launchGame(const std::string& gameName) {
    std::lock_guard<std::mutex> lock(mtx);
    // auto it = games.find(gameName);
    // if (it != games.end()) {
    //     it->second->launch();
    // }
}

std::map<int32_t, std::string> GameMonitor::listGames() {
    //std::lock_guard<std::mutex> lock(mtx);
    // std::stringstream ss;
    // for (const auto& [name, game]: games) {
    //     ss << name << "\n";
    // }
    // list = ss.str();
    return std::map<int32_t, std::string>();
}

void GameMonitor::endGame(const std::string& gameName) {
    std::lock_guard<std::mutex> lock(mtx);
    // auto it = games.find(gameName);
    // if (it != games.end()) {
    //     it->second->stop();
    //     games.erase(it);
    // }
}

void GameMonitor::endAllGames() {
    std::lock_guard<std::mutex> lock(mtx);
    // for (auto& [name, game]: games) {
    //     game->stop();
    // }
    // games.clear();
}

bool GameMonitor::joinGame(int32_t playerId, int32_t gameId) {
    std::lock_guard<std::mutex> lock(mtx);
    // auto it = games.find(gameId);
    // if (it != games.end()) {
    //     it->second->addPlayer(playerId);
    //     return true;
    // }
    return true;
}

bool GameMonitor::startGame(int32_t playerId, int32_t gameId) {
    std::lock_guard<std::mutex> lock(mtx);
    // auto it = games.find(gameId);
    // if (it != games.end()) {
    //     return it->second->start(playerId);
    // }
    return true;
}
