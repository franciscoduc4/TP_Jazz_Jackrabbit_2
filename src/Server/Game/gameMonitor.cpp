#include "gameMonitor.h"

#include <iostream>
#include <sstream>
#include <utility>

#include "../../Common/DTO/gamesList.h"
#include "../../Common/DTO/joinGame.h"
#include "../../Common/DTO/mapsList.h"
#include "../../Common/DTO/startGame.h"
#include "maps/mapsManager.h"

/*
 * Constructor de GameMonitor.
 * Inicializa el monitor del juego con el monitor de la cola, tamaño de la lista de juegos y colas de los jugadores.
 */
GameMonitor::GameMonitor(QueueMonitor& queueMonitor):
        queueMonitor(queueMonitor), gamesListSize(0), playersGameQueues({}), playersGameIds({}) {}

/*
 * Crea un nuevo juego.
 * Bloquea el mutex, verifica que no exista un juego con el mismo nombre, y crea un nuevo juego asignándole una ID única.
 */
void GameMonitor::createGame(uint8_t playerId, uint8_t mapId, GameMode gameMode, uint8_t maxPlayers,
                             CharacterType characterType, const std::string& gameName,
                             const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
    std::cout << "[GM] Attempting to lock mutex in createGame" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in createGame" << std::endl;
    for (auto& [_, game]: games) {
        if (game->getGameName() == gameName) {
            std::cout << "[GM] Game with name " << gameName << " already exists, aborting createGame" << std::endl;
            return;
        }
    }
    uint8_t gameId = games.size();
    queueMonitor.assignGameIdToQueues(gameId, sendQueue);
    std::cout << "[GM] Assigned id to queue for gameId: " << gameId << std::endl;

    auto it = playersRecvQueues.find(playerId);
    if (it != playersRecvQueues.end()) {
        std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> gameQueue = std::make_shared<Queue<std::unique_ptr<CommandDTO>>>();

        playersGameQueues[playerId] = gameQueue;

        games[gameId] = std::make_unique<Game>(gameId, gameName, mapId, playerId, gameMode, maxPlayers,
                                                 characterType, std::move(gameQueue), queueMonitor);
        playersGameIds[playerId] = gameId;
    } else {
        std::cerr << "[GM] Player " << playerId << " not found in playersRecvQueues" << std::endl;
        return;
    }

    std::cout << "[GM] Game created with id: " << gameId << std::endl;

    std::unique_ptr<DTO> dto = std::make_unique<CreateGameDTO>(gameId);
    std::cout << "[GM] Created CreateGameDTO" << std::endl;
    queueMonitor.broadcast(gameId, dto);
    std::cout << "[GM] Broadcasted CreateGameDTO" << std::endl;

    GameInfo gi(gameId, gameName, maxPlayers, 1, mapId);
    std::unique_ptr<DTO> dto2 = std::make_unique<GameUpdateDTO>(gi);
    std::cout << "[GM] Created GameUpdateDTO" << std::endl;
    queueMonitor.broadcast(gameId, dto2);
}

/*
 * Permite que un jugador se una a un juego existente.
 * Bloquea el mutex, verifica que el juego exista y que no esté lleno, y agrega al jugador al juego.
 */
void GameMonitor::joinGame(uint8_t playerId, uint8_t gameId, CharacterType characterType,
                           const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
    std::cout << "[GM] Attempting to lock mutex in joinGame" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in joinGame" << std::endl;
    auto it = games.find(gameId);
    if (it != games.end()) {
        auto& [id, game] = *it;
        if (!game->isFull()) {
            auto it2 = playersRecvQueues.find(playerId);
            if (it2 == playersRecvQueues.end()) {
                std::cerr << "[GM] Player " << playerId << " not found in playersRecvQueues" << std::endl;
                return;
            }
            queueMonitor.assignGameIdToQueues(gameId, sendQueue);
            std::cout << "[GM] Assigned id to queue for gameId: " << gameId << std::endl;
            game->addPlayer(playerId, characterType);
            playersGameQueues[playerId] = game->getRecvQueue();
            playersGameIds[playerId] = gameId;
            std::cout << "[GM] Player " << playerId << " added to game " << gameId << std::endl;
            GameInfo gi = game->getGameInfo();
            auto currentPlayers = gi.currentPlayers;
            std::unique_ptr<DTO> dto = std::make_unique<JoinGameDTO>(playerId, gameId, currentPlayers);
            queueMonitor.broadcast(gameId, dto);
            std::cout << "[GM] Broadcasted JoinGameDTO for gameId: " << static_cast<int>(gameId) << std::endl;

            std::unique_ptr<DTO> dto2 = std::make_unique<GameUpdateDTO>(gi);
            std::cout << "[GM] Created GameUpdateDTO" << std::endl;
            queueMonitor.broadcast(gameId, dto2);
            std::cout << "[GM] Broadcasted GameUpdateDTO for gameId: " << static_cast<int>(gameId) << std::endl;
        } else {
            std::cout << "[GM] Game " << gameId << " is full, player " << playerId << " cannot join" << std::endl;
        }
    } else {
        std::cout << "[GM] Game with id " << gameId << " not found, player " << playerId << " cannot join" << std::endl;
    }
}

/*
 * Inicia un juego.
 * Bloquea el mutex, verifica que el juego esté lleno y no esté ya en ejecución, y luego lanza el juego.
 */
void GameMonitor::startGame(uint8_t playerId, uint8_t gameId,
                            const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
    std::cout << "[GM] Attempting to lock mutex in startGame" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in startGame" << std::endl;
    auto it = games.find(gameId);
    if (it != games.end()) {
        auto& [id, game] = *it;
        if (game->isFull() && !game->isRunning()) {
            std::unique_ptr<DTO> dto = std::make_unique<StartGameDTO>(gameId);
            queueMonitor.broadcast(gameId, dto);
            std::cout << "[GM] Pushed StartGameDTO to send queue" << std::endl;
            game->launch();
            std::cout << "[GM] Game " << (int)gameId << " launched by player " << (int)playerId << std::endl;
        } else {
            std::cout << "[GM] Game " << (int)gameId << " is either not full or already running, cannot start" << std::endl;
        }
    } else {
        std::cout << "[GM] Game with id " << (int)gameId << " not found, cannot start" << std::endl;
    }
}

/*
 * Genera una lista de juegos disponibles.
 * Bloquea el mutex, recopila la información de todos los juegos y la envía a la cola de envío.
 */
void GameMonitor::gamesList(const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
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
}

/*
 * Genera una lista de mapas disponibles.
 * Bloquea el mutex, obtiene la lista de mapas del MapsManager y la envía a la cola de envío.
 */
void GameMonitor::mapsList(const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue) {
    std::cout << "[GM] Attempting to lock mutex in mapsList" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[Game Monitor] Getting maps list" << std::endl;
    auto dto = std::make_unique<MapsListDTO>(MapsManager::getMapIdAndName());
    std::cout << "[Game Monitor] Sending maps list" << std::endl;
    sendQueue->push(std::move(dto));
    std::cout << "[GM] Pushed MapsListDTO to send queue" << std::endl;
}

/*
 * Devuelve el tamaño de la lista de juegos.
 */
uint8_t GameMonitor::getGamesListSize() {
    std::cout << "[GM] Returning games list size: " << gamesListSize << std::endl;
    return gamesListSize;
}

/*
 * Finaliza un juego específico.
 * Bloquea el mutex, encuentra el juego por su nombre y lo elimina.
 */
void GameMonitor::endGame(const std::string& gameName) {
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
}

/*
 * Finaliza todos los juegos.
 * Bloquea el mutex, finaliza y elimina todos los juegos.
 */
void GameMonitor::endAllGames() {
    std::cout << "[GM] Attempting to lock mutex in endAllGames" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in endAllGames" << std::endl;
    for (auto& [id, game]: games) {
        game->endGame();
        std::cout << "[GM] Ended game with id: " << id << std::endl;
    }
    games.clear();
    std::cout << "[GM] Cleared all games" << std::endl;
}

/*
 * Agrega la cola de recepción de un jugador.
 * Bloquea el mutex y agrega la cola de recepción del jugador al mapa de colas de recepción.
 */
void GameMonitor::addPlayerRecvQueue(uint8_t playerId,
                                     const std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>>& recvQueue) {
    std::cout << "[GM] Attempting to lock mutex in addPlayerRecvQueue" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in addPlayerRecvQueue" << std::endl;
    playersRecvQueues[playerId] = recvQueue;
    std::cout << "[GM] Added player " << playerId << " to playersRecvQueues" << std::endl;
}

/*
 * Obtiene la cola de recepción del juego de un jugador.
 * Devuelve un puntero compartido a la cola de recepción del juego del jugador, o nullptr si no se encuentra.
 */
std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> GameMonitor::getPlayerGameQueue(uint8_t playerId) {
    auto it = playersGameQueues.find(playerId);
    if (it == playersGameQueues.end()) {
        std::cerr << "[GM] Player " << playerId << " not found in playersGameQueues" << std::endl;
        return nullptr;
    }
    return playersGameQueues[playerId];
}

/*
 * Obtiene el ID del juego de un jugador.
 * Devuelve el ID del juego del jugador, o 0 si no se encuentra.
 */
uint8_t GameMonitor::getGameId(uint8_t playerId) {
    auto it = playersGameIds.find(playerId);
    if (it == playersGameIds.end()) {
        std::cerr << "[GM] Player " << playerId << " not found in playersGameIds" << std::endl;
        return 0;
    }
    return playersGameIds[playerId];
}

/*
 * Elimina a un jugador de su juego.
 * Bloquea el mutex, elimina al jugador del juego y elimina las referencias en los mapas.
 */
void GameMonitor::removePlayerFromGame(uint8_t playerId) {
    std::cout << "[GM] Attempting to lock mutex in removePlayerFromGame" << std::endl;
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "[GM] Mutex locked in removePlayerFromGame" << std::endl;
    auto it = playersGameIds.find(playerId);
    if (it != playersGameIds.end()) {
        uint8_t gameId = it->second;
        auto it2 = games.find(gameId);
        if (it2 != games.end()) {
            it2->second->removePlayer(playerId);
            playersGameQueues.erase(playerId);
            playersGameIds.erase(playerId);
            std::cout << "[GM] Removed player " << playerId << " from game " << gameId << std::endl;
        } else {
            std::cerr << "[GM] Game with id " << gameId << " not found" << std::endl;
        }
    } else {
        std::cerr << "[GM] Player " << playerId << " not found in playersGameIds" << std::endl;
    }
}
