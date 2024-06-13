#include "game.h"

#include <utility>

Game::Game(uint32_t gameId, std::string gameName, uint32_t mapId, uint32_t playerId,
           GameMode gameMode, uint8_t maxPlayers, CharacterType characterType,
           std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
           QueueMonitor<std::unique_ptr<DTO>>& queueMonitor):
        gameId(gameId),
        gameName(std::move(gameName)),
        mapId(mapId),
        gameMode(gameMode),
        maxPlayers(maxPlayers),
        gameMap({255, 255}, mapId),
        currentPlayers(1),
        gameLoop(recvQueue, queueMonitor, gameMap, gameId) {
    std::cout << "[GAME] Game created" << std::endl;
    gameMap.loadMap(mapId);
    std::cout << "[GAME] Map loaded" << std::endl;
    gameMap.addCharacter(playerId, characterType);
    std::cout << "[GAME] Character added" << std::endl;
}

std::string Game::getGameName() const { return gameName; }

bool Game::isFull() const { return currentPlayers == maxPlayers; }


void Game::addPlayer(uint32_t playerId, CharacterType characterType) {
    gameMap.addCharacter(playerId, characterType);
    currentPlayers++;
}
void Game::removePlayer(uint32_t playerId) {
    gameMap.removeCharacter(playerId);
    currentPlayers--;
}

uint32_t Game::getGameId() const { return gameId; }

GameInfo Game::getGameInfo() { return {gameId, gameName, maxPlayers, currentPlayers}; }

void Game::launch() { gameLoop.start(); }

bool Game::isRunning() { return gameLoop.isRunning(); }

void Game::endGame() {
    gameLoop.stop();
    gameLoop.join();
}

std::unique_ptr<GameDTO> Game::getGameDTO() { return gameMap.getGameDTO(); }