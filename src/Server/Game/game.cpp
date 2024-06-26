#include "game.h"

#include <iostream>
#include <utility>

Game::Game(uint8_t gameId, std::string gameName, uint8_t mapId, uint8_t playerId, GameMode gameMode,
           uint8_t maxPlayers, CharacterType characterType,
           std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
           QueueMonitor& queueMonitor):
        gameId(gameId),
        gameName(std::move(gameName)),
        mapId(mapId),
        mapName(MapsManager::getMapNameById(mapId)),
        gameMode(gameMode),
        maxPlayers(gameMode == GameMode::PARTY_MODE ? maxPlayers : 1),
        gameMap({}, mapId),
        currentPlayers(1),
        recvQueue(std::move(recvQueue)),
        gameLoop(this->recvQueue, queueMonitor, gameMap, gameId) {
    std::cout << "[GAME] Game created with id: " << (int)gameId << " and name: " << this->gameName
              << std::endl;
    gameMap.loadMap(mapId);
    std::cout << "[GAME] Map loaded for mapId: " << (int)mapId << std::endl;
    gameMap.addCharacter(playerId, characterType);
    std::cout << "[GAME] Character added with playerId: " << (int)playerId
              << " and characterType: " << (int)characterType << std::endl;
}

std::string Game::getGameName() const {
    std::cout << "[GAME] getGameName called, returning: " << gameName << std::endl;
    return gameName;
}

bool Game::isFull() const {
    std::cout << "[GAME] isFull called, currentPlayers: " << (int)currentPlayers
              << ", maxPlayers: " << (int)maxPlayers << std::endl;
    return currentPlayers == maxPlayers;
}

void Game::addPlayer(uint8_t playerId, CharacterType characterType) {
    std::cout << "[GAME] addPlayer called with playerId: " << playerId
              << " and characterType: " << (int)characterType << std::endl;
    gameMap.addCharacter(playerId, characterType);
    currentPlayers++;
    std::cout << "[GAME] Player added, currentPlayers now: " << (int)currentPlayers << std::endl;
}

uint8_t Game::getGameId() const {
    std::cout << "[GAME] getGameId called, returning: " << gameId << std::endl;
    return gameId;
}

GameInfo Game::getGameInfo() {
    std::cout << "[GAME] getGameInfo called, returning gameId: " << gameId
              << ", gameName: " << gameName << ", maxPlayers: " << (int)maxPlayers
              << ", currentPlayers: " << (int)currentPlayers << std::endl;
    return {gameId, gameName, maxPlayers, currentPlayers, mapId};
}

void Game::launch() {
    std::cout << "[GAME] launch called, starting gameLoop" << std::endl;
    gameLoop.start();
}

bool Game::isRunning() {
    bool running = gameLoop.isRunning();
    std::cout << "[GAME] isRunning called, returning: " << running << std::endl;
    return running;
}

void Game::removePlayer(uint8_t playerId) {
    std::cout << "[GAME] removePlayer called with playerId: " << (int)playerId << std::endl;
    gameMap.removeCharacter(playerId);
    currentPlayers--;
    std::cout << "[GAME] Player removed, currentPlayers now: " << (int)currentPlayers << std::endl;
    if (currentPlayers == 0) {
        endGame();
    }
}

void Game::endGame() {
    std::cout << "[GAME] endGame called, stopping gameLoop" << std::endl;
    if (this->isRunning()) {
        gameLoop.stop();
        gameLoop.join();
    }
    std::cout << "[GAME] Game loop stopped and joined" << std::endl;
}

std::unique_ptr<GameDTO> Game::getGameDTO() {
    std::cout << "[GAME] getGameDTO called" << std::endl;
    return gameMap.getGameDTO();
}

std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> Game::getRecvQueue() {
    return this->recvQueue;
}