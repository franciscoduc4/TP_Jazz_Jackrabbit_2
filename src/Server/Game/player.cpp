#include "player.h"

#include <sys/socket.h>

/*
 * Constructor de Player.
 * Inicializa un jugador con su socket, monitor del juego, ID del jugador y colas de envío y recepción.
 * También inicia los hilos de envío y recepción.
 */
Player::Player(std::shared_ptr<Socket> socket, GameMonitor& gameMonitor, uint8_t playerId):
        playerId(playerId),
        socket(std::move(socket)),
        sendQueue(std::make_shared<Queue<std::unique_ptr<DTO>>>()),
        recvQueue(std::make_shared<Queue<std::unique_ptr<CommandDTO>>>()),
        sender(this->socket, keepPlaying, inGame, playerId, this->sendQueue),
        receiver(this->socket, keepPlaying, inGame, playerId, gameMonitor, this->recvQueue, this->sendQueue) {
    sender.start();
    receiver.start();
}

/*
 * Cierra las colas de envío y recepción.
 */
void Player::closeQueues() {
    sendQueue->close();
    recvQueue->close();
}

/*
 * Detiene los hilos de envío y recepción.
 */
void Player::stopThreads() {
    sender.stop();
    receiver.stop();
    sender.join();
    receiver.join();
}

/*
 * Cierra el socket del jugador.
 */
void Player::closeSocket() {
    try { 
        socket->shutdown(SHUT_RDWR);
        socket->close();
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

/*
 * Desconecta al jugador, cerrando las colas, el socket y deteniendo los hilos.
 */
void Player::disconnect() {
    keepPlaying.store(false);
    inGame.store(false);
    this->closeQueues();
    this->closeSocket();
    this->stopThreads();
    std::cout << "Player disconnected" << std::endl;
}

/*
 * Verifica si el jugador sigue jugando.
 * Devuelve true si el jugador sigue jugando, false en caso contrario.
 */
bool Player::isPlaying() const { 
    return keepPlaying.load(); 
}

/*
 * Obtiene el ID del jugador.
 * Devuelve el ID del jugador.
 */
uint8_t Player::getPlayerId() const { 
    return playerId; 
}

/*
 * Obtiene la cola de recepción del jugador.
 * Devuelve un puntero compartido a la cola de recepción.
 */
std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> Player::getRecvQueue() {
    return recvQueue;
}
