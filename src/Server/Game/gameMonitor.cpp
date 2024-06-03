#include "gameMonitor.h"
#include <utility>
#include <sstream>

GameMonitor::GameMonitor() {}

void GameMonitor::createGame(const std::string& gameName, int maxPlayers, Player&& player) {
    std::lock_guard<std::mutex> lock(mtx);
    games[gameName] = std::make_unique<Game>(gameName, maxPlayers, std::move(player));
}

void GameMonitor::addPlayer(const std::string& gameName, Player&& player) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(gameName);
    if (it != games.end()) {
        it->second->addPlayer(std::move(player));
    }
}

void GameMonitor::launchGame(const std::string& gameName) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(gameName);
    if (it != games.end()) {
        it->second->launch();
    }
}

void GameMonitor::listGames(std::string& list) {
    std::lock_guard<std::mutex> lock(mtx);
    std::stringstream ss;
    for (const auto& [name, game]: games) {
        ss << name << "\n";
    }
    list = ss.str();
}

void GameMonitor::endGame(const std::string& gameName) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(gameName);
    if (it != games.end()) {
        it->second->stop();
        games.erase(it);
    }
}

void GameMonitor::endAllGames() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& [name, game]: games) {
        game->stop();
    }
    games.clear();
}
