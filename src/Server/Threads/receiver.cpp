#include "receiver.h"

#include <iostream>
#include <memory>
#include <utility>

#include "../CommandHandlers/Lobby/lobbyCommand.h"

/*
 * Constructor de ReceiverThread.
 * Inicializa el receptor con el socket, indicadores de estado del juego, el ID del jugador, el monitor del juego y las colas de recepción y envío.
 */
ReceiverThread::ReceiverThread(const std::shared_ptr<Socket>& socket,
                               std::atomic<bool>& keepPlaying, std::atomic<bool>& inGame,
                               uint8_t playerId, GameMonitor& gameMonitor,
                               const std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>>& recvQueue,
                               const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue):
        playerId(playerId),
        serializer(socket, keepPlaying, inGame),
        deserializer(socket, keepPlaying, inGame),
        keepPlaying(keepPlaying),
        inGame(inGame),
        gameMonitor(gameMonitor),
        recvQueue(recvQueue),
        sendQueue(sendQueue) {
    std::cout << "[SERVER RECEIVER] ReceiverThread initialized" << std::endl;
}

/*
 * Método runLobby.
 * Escucha y maneja comandos en el lobby mientras el jugador no esté en una partida.
 */
void ReceiverThread::runLobby() {
    if (inGame.load())
        return;

    std::cout << "[SERVER RECEIVER LOBBY] Waiting for command" << std::endl;
    std::unique_ptr<CommandDTO> command = deserializer.getCommand(playerId);
    if (command == nullptr) {
        std::cout << "[SERVER RECEIVER LOBBY] No command received, continuing" << std::endl;
        return;
    }
    if (inGame.load())
        return;

    std::cout << "[SERVER RECEIVER LOBBY] Command received" << std::endl;

    auto handler = LobbyCommandHandler::createHandler(std::move(command), gameMonitor.getGameId(playerId));
    std::cout << "[SERVER RECEIVER LOBBY] Handler created" << std::endl;
    if (inGame.load() || handler == nullptr)
        return;

    handler->execute(gameMonitor, inGame, sendQueue);

    std::cout << "[SERVER RECEIVER LOBBY] Command executed" << std::endl;
}

/*
 * Método runGame.
 * Escucha y maneja comandos durante la partida, agregándolos a la cola del juego del jugador.
 */
void ReceiverThread::runGame() {
    std::cout << "[SERVER RECEIVER] Waiting to receive command" << std::endl;
    std::unique_ptr<CommandDTO> commandDTO = deserializer.getCommand(playerId);
    if (commandDTO) {
        std::cout << "[SERVER RECEIVER] Command received, pushing to recvQueue" << std::endl;
        try {
            gameMonitor.getPlayerGameQueue(playerId)->push(std::move(commandDTO));
        } catch (const std::exception& e) {
            this->keepPlaying.store(false);
            this->inGame.store(false);
            std::cerr << "[SERVER RECEIVER] Failed pushing to game queue: " << e.what() << std::endl;
        }
    } else {
        std::cout << "[SERVER RECEIVER] No command received (null commandDTO)" << std::endl;
    }
}

/*
 * Método run del hilo receptor.
 * Maneja el ciclo de vida del receptor, alternando entre el lobby y la partida según el estado del jugador.
 */
void ReceiverThread::run() {
    std::cout << "[SERVER RECEIVER] Receiver thread started" << std::endl;
    std::cout << "[SERVER RECEIVER] Running Lobby..." << std::endl;
    while (keepPlaying.load() && !inGame.load()) {
        try {
            this->runLobby();
        } catch (const std::exception& e) {
            std::cerr << "[SERVER RECEIVER] Exception: " << e.what() << std::endl;
            if (!inGame.load() || !keepPlaying.load()) {
                std::cout << "[SERVER RECEIVER] Socket was closed, exiting receiver thread" << std::endl;
                return;
            }
        }
    }
    std::cout << "[SERVER RECEIVER] Running Game..." << std::endl;
    while (keepPlaying.load() && inGame.load()) {
        try {
            this->runGame();
        } catch (const std::exception& e) {
            std::cerr << "[SERVER RECEIVER] Exception: " << e.what() << std::endl;
            if (!inGame.load() || !keepPlaying.load()) {
                std::cout << "[SERVER RECEIVER] Socket was closed, exiting receiver thread" << std::endl;
                gameMonitor.removePlayerFromGame(playerId);
                return;
            }
        }
    }
    gameMonitor.removePlayerFromGame(playerId);
    std::cout << "[SERVER RECEIVER] Receiver thread exiting" << std::endl;
}
