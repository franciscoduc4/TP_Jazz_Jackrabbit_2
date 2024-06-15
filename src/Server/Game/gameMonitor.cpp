#include "gameMonitor.h"

#include <sstream>
#include <utility>

#include "../../Common/DTO/mapsList.h"
#include "../../Common/DTO/gamesList.h"
#include "../../Common/DTO/joinGame.h"

#include "maps/mapsManager.h"

GameMonitor::GameMonitor(QueueMonitor<std::unique_ptr<DTO>>& queueMonitor):
        queueMonitor(queueMonitor) {}

bool GameMonitor::createGame(uint32_t playerId, uint32_t mapId, std::string mapName,
                             GameMode gameMode, uint8_t maxPlayers, CharacterType characterType,
                             std::string gameName,
                             std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                             uint32_t gameId,
                             std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& [id, game]: games) {
        if (game->getGameName() == gameName) {
            return false;
        }
    }
    queueMonitor.assignGameIdToQueues(gameId, sendQueue);
    games[gameId] = std::make_unique<Game>(gameId, gameName, playerId, mapName, gameMode,
                                           maxPlayers, characterType, recvQueue, queueMonitor);

    return true;
}

void GameMonitor::joinGame(uint32_t playerId, uint32_t gameId, CharacterType characterType,
                           std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
    std::lock_guard<std::mutex> lock(mtx);
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
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(gameId);
    if (it != games.end()) {
        auto& [id, game] = *it;
        if (game->isFull() && !game->isRunning()) {
            game->launch();
        }
    }
}

void GameMonitor::gamesList(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
    std::lock_guard<std::mutex> lock(mtx);
    std::unordered_map<uint32_t, GameInfo> list;
    for (auto& [id, game]: games) {
        GameInfo gameInfo = game->getGameInfo();
        list[id] = gameInfo;
    }
    gamesListSize = list.size();
    auto dto = std::make_unique<GamesListDTO>(list);
    sendQueue->push(std::move(dto));
}

void GameMonitor::mapsList(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[Game Monitor] Getting maps list" << std::endl;
    auto dto = std::make_unique<MapsListDTO>(MapsManager::getMapIdAndName());
    std::cout << "[Game Monitor] Sending maps list" << std::endl;
    sendQueue->push(std::move(dto));
}

uint8_t GameMonitor::getCurrentPlayers(uint32_t gameId) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = games.find(gameId);
    if (it != games.end()) {
        auto& [id, game] = *it;
    }
    return 0;
}

uint32_t GameMonitor::getGamesListSize() { return gamesListSize; }

// void GameMonitor::broadcastToGame(uint32_t gameId, std::unique_ptr<CommandDTO> command) {
//     std::lock_guard<std::mutex> lock(mtx);
//     auto it = games.find(gameId);
//     if (it != games.end()) {
//         auto& [id, game] = *it;
//         game->broadcast(std::move(command));
//     }
// }

void GameMonitor::endGame(const std::string& gameName) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto it = games.begin(); it != games.end(); ++it) {
        if (it->second->getGameName() == gameName) {
            it->second->endGame();
            games.erase(it);
            return;
        }
    }
}

void GameMonitor::endAllGames() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& [id, game]: games) {
        game->endGame();
    }
    games.clear();
}