#include "game.h"

#include <utility>

Game::Game(int32_t gameId, std::string gameName, int32_t playerId, Episode episode,
           GameMode gameMode, uint8_t maxPlayers, CharacterType characterType,
           std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
           QueueMonitor<std::unique_ptr<GameDTO>>& queueMonitor):
        gameId(gameId),
        gameName(std::move(gameName)),
        episode(episode),
        gameMode(gameMode),
        maxPlayers(maxPlayers),
        gameMap({100, 100}),
        currentPlayers(1),
        gameLoop(recvQueue, queueMonitor, gameMap) {
    gameMap.addCharacter(playerId, characterType, {});
}

std::string Game::getGameName() const { return gameName; }

bool Game::isFull() const { return currentPlayers == maxPlayers; }


void Game::addPlayer(int32_t playerId, CharacterType characterType) {
    gameMap.addCharacter(playerId, characterType, {});
    currentPlayers++;
}
void Game::removePlayer(int32_t playerId) {
    gameMap.removeCharacter(playerId);
    currentPlayers--;
}

int32_t Game::getGameId() const { return gameId; }

GameInfo Game::getGameInfo() {
    return {gameId, gameName, maxPlayers, currentPlayers};
}

void Game::launch() { gameLoop.start(); }

void Game::endGame() {
    gameLoop.stop();
    gameLoop.join();
}