#include "game.h"

Game::Game(const std::string& name, int maxPlayers, Player&& firstPlayer):
        name(name),
        maxPlayers(maxPlayers),
        currentPlayers(1),
        recvQueue(),
        queueMonitor(),
        players(),
        receiverThreads(),
        senderThreads(),
        running(false),
        gameStatus(),
        gameLoop(recvQueue, queueMonitor, gameStatus) {}

void Game::addPlayer(Player&& player) {
    initPlayerThreads(player);
    players.emplace_back(std::move(player));
    currentPlayers++;
    std::unique_ptr<Character> playerCharacter = player.getCharacter();
    gameStatus->addCharacter(std::move(playerCharacter));
}

void Game::initPlayerThreads(Player& player) {
    receiverThreads.emplace(player.getId(), player.initReceiver(recvQueue));
    receiverThreads[player.getId()]->start();

    senderThreads.emplace(player.getId(), player.initSender(queueMonitor->createQueue()));
    senderThreads[player.getId()]->start();
}

void Game::removePlayer(int playerId) {
    auto it = std::find_if(players.begin(), players.end(),
                           [playerId](const Player& player) { return player.getId() == playerId; });

    if (it == players.end()) {
        throw std::runtime_error("Player not found");
    }

    receiverThreads[playerId]->stop();
    receiverThreads[playerId]->join();
    receiverThreads.erase(playerId);

    senderThreads[playerId]->stop();
    senderThreads[playerId]->join();
    senderThreads.erase(playerId);

    players.erase(it);
    currentPlayers--;
}

void Game::launch() {
    if (isRunning()) {
        throw std::runtime_error("Game is already running");
    }
    gameLoop.start();
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

Game::~Game() {
    for (auto& player: players) {
        removePlayer(player.getId());
    }
}