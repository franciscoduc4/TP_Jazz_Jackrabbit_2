#include "gameMonitor.h"
#include <sstream>
#include <utility>
#include "../../Common/DTO/mapsList.h"
#include "../../Common/DTO/gamesList.h"
#include "../../Common/DTO/joinGame.h"
#include "maps/mapsManager.h"

GameMonitor::GameMonitor(QueueMonitor<std::unique_ptr<DTO>>& queueMonitor):
        queueMonitor(queueMonitor) {}

void GameMonitor::createGame(uint32_t playerId, uint32_t mapId,
                             GameMode gameMode, uint8_t maxPlayers, CharacterType characterType,
                             std::string gameName,
                             std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                             uint32_t gameId,
                             std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    std::cout << "[GM] Attempting to lock mutex in createGame" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in createGame" << std::endl;
    for (auto& [id, game]: games) {
        if (game->getGameName() == gameName) {
            return;
        }
    }
    queueMonitor.assignGameIdToQueues(gameId, sendQueue);
    std::cout << "[GM] assigned id to queue" << std::endl;
    games[gameId] = std::make_unique<Game>(gameId, gameName, mapId, playerId, gameMode,
                                           maxPlayers, characterType, recvQueue, queueMonitor);
    std::cout << "[GM] Game created" << std::endl;

    auto dto = std::make_unique<CreateGameDTO>(gameId);
    std::cout << "[GM] created dto" << std::endl;
    queueMonitor.broadcast(gameId, std::move(dto));
    std::cout << "[GM] broadcasted dto" << std::endl;
}

void GameMonitor::joinGame(uint32_t playerId, uint32_t gameId, CharacterType characterType,
                           std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    std::cout << "[GM] Attempting to lock mutex in joinGame" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in joinGame" << std::endl;
    auto it = games.find(gameId);
    if (it != games.end()) {
        auto& [id, game] = *it;
        if (!game->isFull()) {
            queueMonitor.assignGameIdToQueues(gameId, sendQueue);
            game->addPlayer(playerId, characterType);
            auto currentPlayers = game->getGameInfo().currentPlayers;
            auto dto = std::make_unique<JoinGameDTO>(playerId, gameId, currentPlayers);
            queueMonitor.broadcast(gameId, std::move(dto));
        }
    }
}

void GameMonitor::startGame(uint32_t playerId, uint32_t gameId) {
    std::cout << "[GM] Attempting to lock mutex in startGame" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in startGame" << std::endl;
    auto it = games.find(gameId);
    if (it != games.end()) {
        auto& [id, game] = *it;
        if (game->isFull() && !game->isRunning()) {
            game->launch();
        }
    }
}

void GameMonitor::gamesList(std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    std::cout << "[GM] Attempting to lock mutex in gamesList" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in gamesList" << std::endl;
    std::map<uint32_t, GameInfo> list;
    for (auto& [id, game]: games) {
        GameInfo gameInfo = game->getGameInfo();
        list[id] = gameInfo;
    }
    gamesListSize = list.size();
    auto dto = std::make_unique<GamesListDTO>(list);
    sendQueue->push(std::move(dto));
}

void GameMonitor::mapsList(std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    std::cout << "[GM] Attempting to lock mutex in mapsList" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in mapsList" << std::endl;
    auto dto = std::make_unique<MapsListDTO>(MapsManager::getMapIdAndName());
    sendQueue->push(std::move(dto));
}

uint8_t GameMonitor::getCurrentPlayers(uint32_t gameId) {
    std::cout << "[GM] Attempting to lock mutex in getCurrentPlayers" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in getCurrentPlayers" << std::endl;
    auto it = games.find(gameId);
    if (it != games.end()) {
        auto& [id, game] = *it;
    }
    return 0;
}

uint32_t GameMonitor::getGamesListSize() { return gamesListSize; }

void GameMonitor::endGame(const std::string& gameName) {
    std::cout << "[GM] Attempting to lock mutex in endGame" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in endGame" << std::endl;
    for (auto it = games.begin(); it != games.end(); ++it) {
        if (it->second->getGameName() == gameName) {
            it->second->endGame();
            games.erase(it);
            return;
        }
    }
}

void GameMonitor::endAllGames() {
    std::cout << "[GM] Attempting to lock mutex in endAllGames" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in endAllGames" << std::endl;
    for (auto& [id, game]: games) {
        game->endGame();
    }
    games.clear();
}
