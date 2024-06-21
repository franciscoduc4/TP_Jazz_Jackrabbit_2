#include "player.h"

#include <sys/socket.h>


Player::Player(std::shared_ptr<Socket> socket, GameMonitor& gameMonitor, uint8_t playerId):
        playerId(playerId),
        socket(std::move(socket)),
        sendQueue(std::make_shared<Queue<std::unique_ptr<DTO>>>()),
        recvQueue(std::make_shared<Queue<std::unique_ptr<CommandDTO>>>()),
        sender(this->socket, keepPlaying, inGame,  playerId, this->sendQueue),
        receiver(this->socket, keepPlaying, inGame, playerId, gameMonitor, this->recvQueue, this->sendQueue){
    sender.start();
    receiver.start();
}

void Player::closeQueues() {
    sendQueue->close();
    recvQueue->close();
}

void Player::stopThreads() {
    sender.stop();
    receiver.stop();
    sender.join();
    receiver.join();
}

void Player::closeSocket() {
    socket->shutdown(SHUT_RDWR);
    socket->close();
}

void Player::disconnect() {
    keepPlaying.store(false);
    inGame.store(false);
    this->closeQueues();
    this->stopThreads();
    this->closeSocket();
}

bool Player::isPlaying() const { return keepPlaying.load(); }

uint8_t Player::getPlayerId() const { return playerId; }

std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> Player::getRecvQueue() {
    return recvQueue;
}