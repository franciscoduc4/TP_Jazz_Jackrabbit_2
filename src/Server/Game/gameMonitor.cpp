#include "gameMonitor.h"

#include <iostream>
#include <sstream>
#include <utility>

#include "../../Common/DTO/gamesList.h"
#include "../../Common/DTO/joinGame.h"
#include "../../Common/DTO/mapsList.h"
#include "../../Common/DTO/startGame.h"
#include "maps/mapsManager.h"

GameMonitor::GameMonitor(QueueMonitor<std::unique_ptr<DTO>>& queueMonitor):
        queueMonitor(queueMonitor), gamesListSize(0) {}

void GameMonitor::createGame(uint8_t playerId, uint8_t mapId, GameMode gameMode, uint8_t maxPlayers,
                             CharacterType characterType, std::string gameName,
                             std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue,
                             std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    try {
        std::cout << "[GM] Attempting to lock mutex in createGame" << std::endl;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "[GM] Mutex locked in createGame" << std::endl;
        for (auto& [_, game]: games) {
            if (game->getGameName() == gameName) {
                std::cout << "[GM] Game with name " << gameName
                          << " already exists, aborting createGame" << std::endl;
                return;
            }
        }
        uint8_t gameId = games.size();
        queueMonitor.assignGameIdToQueues(gameId, sendQueue);
        std::cout << "[GM] Assigned id to queue for gameId: " << gameId << std::endl;
        games[gameId] = std::make_unique<Game>(gameId, gameName, mapId, playerId, gameMode,
                                               maxPlayers, characterType, recvQueue, queueMonitor);
        std::cout << "[GM] Game created with id: " << gameId << std::endl;

        auto dto = std::make_unique<CreateGameDTO>(gameId);
        std::cout << "[GM] Created CreateGameDTO" << std::endl;
        queueMonitor.broadcast(gameId, std::move(dto));
        std::cout << "[GM] Broadcasted CreateGameDTO" << std::endl;

        GameInfo gi(gameId, gameName, maxPlayers, 1, mapId);
        auto dto2 = std::make_unique<GameUpdateDTO>(gi);
        std::cout << "[GM] Created GameUpdateDTO" << std::endl;
        queueMonitor.broadcast(gameId, std::move(dto2));
    } catch (const std::exception& e) {
        std::cerr << "[GM] Error in createGame: " << e.what() << std::endl;
    }
}

void GameMonitor::joinGame(uint8_t playerId, uint8_t gameId, CharacterType characterType,
                           std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    try {
        std::cout << "[GM] Attempting to lock mutex in joinGame" << std::endl;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "[GM] Mutex locked in joinGame" << std::endl;
        auto it = games.find(gameId);
        if (it != games.end()) {
            auto& [id, game] = *it;
            if (!game->isFull()) {
                queueMonitor.assignGameIdToQueues(gameId, sendQueue);
                std::cout << "[GM] Assigned id to queue for gameId: " << gameId << std::endl;
                game->addPlayer(playerId, characterType);
                std::cout << "[GM] Player " << playerId << " added to game " << gameId << std::endl;
                GameInfo gi = game->getGameInfo();
                auto currentPlayers = gi.currentPlayers;
                auto dto = std::make_unique<JoinGameDTO>(playerId, gameId, currentPlayers);
                queueMonitor.broadcast(gameId, std::move(dto));
                std::cout << "[GM] Broadcasted JoinGameDTO for gameId: " << gameId << std::endl;

                auto dto2 = std::make_unique<GameUpdateDTO>(gi);
                std::cout << "[GM] Created GameUpdateDTO" << std::endl;
                queueMonitor.broadcast(gameId, std::move(dto2));
            } else {
                std::cout << "[GM] Game " << gameId << " is full, player " << playerId
                          << " cannot join" << std::endl;
            }
        } else {
            std::cout << "[GM] Game with id " << gameId << " not found, player " << playerId
                      << " cannot join" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "[GM] Error in joinGame: " << e.what() << std::endl;
    }
}

void GameMonitor::startGame(uint8_t playerId, uint8_t gameId,
                            std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    try {
        std::cout << "[GM] Attempting to lock mutex in startGame" << std::endl;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "[GM] Mutex locked in startGame" << std::endl;
        auto it = games.find(gameId);
        if (it != games.end()) {
            auto& [id, game] = *it;
            if (game->isFull() && !game->isRunning()) {
                auto dto = std::make_unique<StartGameDTO>(gameId);
                sendQueue->push(std::move(dto));
                std::cout << "[GM] Pushed StartGameDTO to send queue" << std::endl;
                game->launch();
                std::cout << "[GM] Game " << (int)gameId << " launched by player " << (int)playerId
                          << std::endl;
            } else {
                std::cout << "[GM] Game " << (int)gameId
                          << " is either not full or already running, cannot start" << std::endl;
            }
        } else {
            std::cout << "[GM] Game with id " << (int)gameId << " not found, cannot start"
                      << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "[GM] Error in startGame: " << e.what() << std::endl;
    }
}

void GameMonitor::gamesList(std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    try {
        std::cout << "[GM] Attempting to lock mutex in gamesList" << std::endl;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "[GM] Mutex locked in gamesList" << std::endl;
        std::unordered_map<uint8_t, GameInfo> list;
        for (auto& [id, game]: games) {
            GameInfo gameInfo = game->getGameInfo();
            list[id] = gameInfo;
            std::cout << "[GM] Added game " << id << " to games list" << std::endl;
        }
        gamesListSize = list.size();
        auto dto = std::make_unique<GamesListDTO>(list);
        sendQueue->push(std::move(dto));
        std::cout << "[GM] Pushed GamesListDTO to send queue" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[GM] Error in gamesList: " << e.what() << std::endl;
    }
}

void GameMonitor::mapsList(std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue) {
    try {
        std::cout << "[GM] Attempting to lock mutex in mapsList" << std::endl;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "[Game Monitor] Getting maps list" << std::endl;
        auto dto = std::make_unique<MapsListDTO>(MapsManager::getMapIdAndName());
        std::cout << "[Game Monitor] Sending maps list" << std::endl;
        sendQueue->push(std::move(dto));
        std::cout << "[GM] Pushed MapsListDTO to send queue" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[GM] Error in mapsList: " << e.what() << std::endl;
    }
}

uint8_t GameMonitor::getCurrentPlayers(uint8_t gameId) {
    try {
        std::cout << "[GM] Attempting to lock mutex in getCurrentPlayers" << std::endl;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "[GM] Mutex locked in getCurrentPlayers" << std::endl;
        auto it = games.find(gameId);
        if (it != games.end()) {
            auto& [id, game] = *it;
            std::cout << "[GM] Found game with id: " << gameId << std::endl;
            return game->getGameInfo().currentPlayers;
        }
        std::cout << "[GM] Game with id " << gameId << " not found" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "[GM] Error in getCurrentPlayers: " << e.what() << std::endl;
        return 0;
    }
}

uint8_t GameMonitor::getGamesListSize() {
    std::cout << "[GM] Returning games list size: " << gamesListSize << std::endl;
    return gamesListSize;
}

void GameMonitor::endGame(const std::string& gameName) {
    try {
        std::cout << "[GM] Attempting to lock mutex in endGame" << std::endl;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "[GM] Mutex locked in endGame" << std::endl;
        for (auto it = games.begin(); it != games.end(); ++it) {
            if (it->second->getGameName() == gameName) {
                it->second->endGame();
                games.erase(it);
                std::cout << "[GM] Ended and erased game with name: " << gameName << std::endl;
                return;
            }
        }
        std::cout << "[GM] Game with name " << gameName << " not found" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[GM] Error in endGame: " << e.what() << std::endl;
    }
}

void GameMonitor::endAllGames() {
    try {
        std::cout << "[GM] Attempting to lock mutex in endAllGames" << std::endl;
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "[GM] Mutex locked in endAllGames" << std::endl;
        for (auto& [id, game]: games) {
            game->endGame();
            std::cout << "[GM] Ended game with id: " << id << std::endl;
        }
        games.clear();
        std::cout << "[GM] Cleared all games" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[GM] Error in endAllGames: " << e.what() << std::endl;
    }
}
