#include "gamesMonitor.h"

GamesMonitor::GamesMonitor() {}

void GamesMonitor::addPlayer(const std::string& gameName, std::shared_ptr<PlayerHandler> player) {
    std::lock_guard<std::mutex> lock(mtx);

    if (games.find(gameName) == games.end()) {
        throw std::runtime_error("Game not found");
    }

    if (games[gameName]->isFull()) {
        throw std::runtime_error("Game is full");
    }

    games[gameName]->addPlayer(player);
}

void GamesMonitor::removePlayer(const std::string& gameName,
                                std::shared_ptr<PlayerHandler> player) {
    std::lock_guard<std::mutex> lock(mtx);

    if (games.find(gameName) == games.end()) {
        throw std::runtime_error("Game not found");
    }

    games[gameName]->removePlayer(player);
}

void GamesMonitor::addGame(std::shared_ptr<Game> game) {
    std::lock_guard<std::mutex> lock(mtx);

    if (games.find(game->getName()) != games.end()) {
        throw std::runtime_error("Game already exists");
    }

    games[game->getName()] = game;
}

void GamesMonitor::removeGame(const std::string& gameName) {
    std::lock_guard<std::mutex> lock(mtx);

    if (games.find(gameName) == games.end()) {
        throw std::runtime_error("Game not found");
    }

    games.erase(gameName);
}