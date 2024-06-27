#include "game.h"

#include <iostream>
#include <utility>

/*
 * Constructor de Game.
 * Inicializa un nuevo juego con su ID, nombre, mapa, ID del jugador, modo de juego, cantidad máxima de jugadores,
 * tipo de carácter del jugador, cola de recepción y el monitor de colas.
 */
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
    std::cout << "[GAME] Game created with id: " << (int)gameId << " and name: " << this->gameName << std::endl;
    gameMap.loadMap(mapId);
    std::cout << "[GAME] Map loaded for mapId: " << (int)mapId << std::endl;
    gameMap.addCharacter(playerId, characterType);
    std::cout << "[GAME] Character added with playerId: " << (int)playerId << " and characterType: " << (int)characterType << std::endl;
}

/*
 * Devuelve el nombre del juego.
 */
std::string Game::getGameName() const {
    std::cout << "[GAME] getGameName called, returning: " << gameName << std::endl;
    return gameName;
}

/*
 * Verifica si el juego está lleno.
 */
bool Game::isFull() const {
    std::cout << "[GAME] isFull called, currentPlayers: " << (int)currentPlayers << ", maxPlayers: " << (int)maxPlayers << std::endl;
    return currentPlayers == maxPlayers;
}

/*
 * Agrega un jugador al juego.
 */
void Game::addPlayer(uint8_t playerId, CharacterType characterType) {
    std::cout << "[GAME] addPlayer called with playerId: " << playerId << " and characterType: " << (int)characterType << std::endl;
    gameMap.addCharacter(playerId, characterType);
    currentPlayers++;
    std::cout << "[GAME] Player added, currentPlayers now: " << (int)currentPlayers << std::endl;
}

/*
 * Devuelve el ID del juego.
 */
uint8_t Game::getGameId() const {
    std::cout << "[GAME] getGameId called, returning: " << gameId << std::endl;
    return gameId;
}

/*
 * Devuelve información sobre el juego.
 */
GameInfo Game::getGameInfo() {
    std::cout << "[GAME] getGameInfo called, returning gameId: " << gameId << ", gameName: " << gameName << ", maxPlayers: " << (int)maxPlayers << ", currentPlayers: " << (int)currentPlayers << std::endl;
    return {gameId, gameName, maxPlayers, currentPlayers, mapId};
}

/*
 * Lanza el bucle del juego.
 */
void Game::launch() {
    std::cout << "[GAME] launch called, starting gameLoop" << std::endl;
    gameLoop.start();
}

/*
 * Verifica si el bucle del juego está en ejecución.
 */
bool Game::isRunning() {
    bool running = gameLoop.isRunning();
    std::cout << "[GAME] isRunning called, returning: " << running << std::endl;
    return running;
}

/*
 * Elimina un jugador del juego.
 */
void Game::removePlayer(uint8_t playerId) {
    std::cout << "[GAME] removePlayer called with playerId: " << (int)playerId << std::endl;
    gameMap.removeCharacter(playerId);
    currentPlayers--;
    std::cout << "[GAME] Player removed, currentPlayers now: " << (int)currentPlayers << std::endl;
    if (currentPlayers == 0) {
        endGame();
    }
}

/*
 * Finaliza el juego.
 * Detiene y une el bucle del juego si está en ejecución.
 */
void Game::endGame() {
    std::cout << "[GAME] endGame called, stopping gameLoop" << std::endl;
    if (this->isRunning()) {
        gameLoop.stop();
        gameLoop.join();
    }
    std::cout << "[GAME] Game loop stopped and joined" << std::endl;
}

/*
 * Devuelve el estado actual del juego en forma de GameDTO.
 */
std::unique_ptr<GameDTO> Game::getGameDTO() {
    std::cout << "[GAME] getGameDTO called" << std::endl;
    return gameMap.getGameDTO();
}

/*
 * Devuelve la cola de recepción del juego.
 */
std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> Game::getRecvQueue() {
    return this->recvQueue;
}
