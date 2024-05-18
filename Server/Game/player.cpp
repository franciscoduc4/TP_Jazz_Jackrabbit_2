#include "player.h"
#include  <utility>

Player::Player(Socket&& socket):
        socket(std::move(socket)), 
        id(socket.getSocketId()), 
        protocol(std::move(socket)), 
        gameName(""), 
        name(""), 
        inGame(false) {}

std::string Player::getGameName() const { return gameName; }

std::string Player::getName() const { return name; }

int Player::getId() const { return id; }

void Player::setInGame() { inGame = true; }

std::shared_ptr<ReceiverThread> Player::initReceiver(Queue<GameTypes::Action>& recvQueue) {
    receiver = std::make_shared<ReceiverThread>(protocol, recvQueue);
    return receiver;
}

std::shared_ptr<SenderThread> Player::initSender(
        std::shared_ptr<Queue<GameTypes::Event>> sendQueue) {
    sender = std::make_shared<SenderThread>(protocol, sendQueue);
    return sender;
}

Socket& Player::getSocketRef() { return socket; }


