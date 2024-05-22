#include "player.h"

Player::Player(Protocol&& protocol):
        protocol(std::move(protocol)),
        id(protocol.getId()),
        gameName(""),
        name(""),
        inGame(false) {}

std::string Player::getGameName() const { return gameName; }

std::string Player::getName() const { return name; }

int Player::getId() const { return id; }

void Player::setInGame() { inGame = true; }

std::unique_ptr<ReceiverThread> Player::initReceiver(
        std::shared_ptr<Queue<GameTypes::Action>> recvQueue) {
    receiver = std::make_unique<ReceiverThread>(std::make_shared<Protocol>(std::move(protocol)),
                                                recvQueue);
    return std::move(receiver);
}

std::unique_ptr<SenderThread> Player::initSender(std::shared_ptr<Queue<std::string>> sendQueue) {
    sender = std::make_unique<SenderThread>(std::make_shared<Protocol>(std::move(protocol)),
                                            sendQueue);
    return std::move(sender);
}

void Player::setCharacter(std::unique_ptr<Character>&& character) {
    this->character = std::move(character);
}

std::unique_ptr<Character> Player::getCharacter() { return std::move(character); }
