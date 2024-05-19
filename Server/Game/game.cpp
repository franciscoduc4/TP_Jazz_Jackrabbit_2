#include "game.h"


Game::Game(std::string name, int maxPlayers, Player&& firstPlayer):
        name(name),
        maxPlayers(maxPlayers),
        currentPlayers(1),
        gameLoop(),
        recvQueue(),
        players(),
        receiverThreads(),
        broadcaster(),
        running(false) {}

void Game::addPlayer(Player&& player) {
    initPlayerThreads(player);
    players.emplace_back(std::move(player));
    currentPlayers++;
}

void Game::initPlayerThreads(Player& player) {
    receiverThreads.emplace(player.getId(), player.initReceiver(recvQueue));
    receiverThreads[player.getId()]->start();

    broadcaster.addSender(player);
}

void Game::removePlayer(int playerId) {
    auto it = std::find_if(players.begin(), players.end(),
                           [playerId](const Player& player) { return player.getId() == playerId; });

    if (it == players.end()) {
        throw std::runtime_error("Player not found");
    }

    broadcaster.removeSender(playerId);
    receiverThreads[playerId]->stop();
    receiverThreads[playerId]->join();
    receiverThreads.erase(playerId);

    players.erase(it);
    currentPlayers--;
}

void Game::launch() {
    if (isRunning()) {
        throw std::runtime_error("Game is already running");
    }
    broadcaster.start();
    // gameLoop.start();
    running = true;
}

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

int Game::getMaxPlayers() const { return maxPlayers; }

int Game::getCurrentPlayers() const { return currentPlayers; }
