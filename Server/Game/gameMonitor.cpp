#include "gameMonitor.h"


GameMonitor::GameMonitor() {}

void GameMonitor::createGame(const std::string& gameName, int maxPlayers, Player&& player) {
    std::lock_guard<std::mutex> lock(mtx);

    if (games.find(gameName) != games.end()) {
        throw std::runtime_error("Game already exists");
    }

    Game game(gameName, maxPlayers, std::move(player));
    games.try_emplace(gameName, std::move(game));
    player.setInGame();
}

void GameMonitor::addPlayer(const std::string& gameName, Player&& player) {
    std::lock_guard<std::mutex> lock(mtx);

    if (games.find(gameName) == games.end()) {
        throw std::runtime_error("Game not found");
    }

    if (games[gameName].isFull()) {
        throw std::runtime_error("Game is full");
    }

    games[gameName].addPlayer(std::move(player));
    player.setInGame();

    if (games[gameName].isFull()) {
        launchGame(gameName);
    }
}

void GameMonitor::launchGame(const std::string& gameName) {
    std::lock_guard<std::mutex> lock(mtx);

    if (games.find(gameName) == games.end()) {
        throw std::runtime_error("Game not found");
    }

    games[gameName].launch();
}

void GameMonitor::listGames(std::string& list) {
    std::lock_guard<std::mutex> lock(mtx);

    list = std::accumulate(games.begin(), games.end(), std::string{},
                           [](const std::string& acc, const auto& gamePair) {
                               const Game& game = gamePair.second;
                               return acc + game.getName() + "\0 " +
                                      std::to_string(game.getCurrentPlayers()) + "/" +
                                      std::to_string(game.getMaxPlayers()) + "\n";
                           });
}

void GameMonitor::endGame(const std::string& gameName) {
    std::lock_guard<std::mutex> lock(mtx);

    if (games.find(gameName) == games.end()) {
        throw std::runtime_error("Game not found");
    }
    games[gameName].stop();
    games.erase(gameName);
}

void GameMonitor::endAllGames() {
    std::lock_guard<std::mutex> lock(mtx);

    for (auto& game: games) {
        game.second.stop();
    }

    games.clear();
}
