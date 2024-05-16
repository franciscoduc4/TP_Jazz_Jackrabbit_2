#include "game.h"

#include <algorithm>

Game::Game(std::string name, int maxPlayers):
        name(name),
        maxPlayers(maxPlayers),
        currentPlayers(1),
        gameLoop(),
        players(),
        running(false) {}

void Game::addPlayer(std::shared_ptr<PlayerHandler> player) {
    players.emplace_back(player);
    currentPlayers++;
}


void Game::removePlayer(std::shared_ptr<PlayerHandler> player) {
    players.erase(std::remove_if(players.begin(), players.end(),
                                 [&player](const std::shared_ptr<PlayerHandler>& p) {
                                     return p == player;
                                 }),
                  players.end());
    currentPlayers--;
}

// void Game::launch() {
//     if (isRunning()) {
//         throw std::runtime_error("Game is already running");
//     }
//     gameLoop.start();
//     running = true;
// }

void Game::stop() {
    if (!isRunning()) {
        throw std::runtime_error("Game is not running");
    }
    gameLoop.stop();
    running = false;
}

bool Game::isRunning() const { return running; }

bool Game::isFull() const { return currentPlayers == maxPlayers; }

std::string Game::getName() const { return name; }