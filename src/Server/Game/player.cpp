#include "player.h"

#include <sys/socket.h>

#include "../Physics/character.h"

Player::Player(std::shared_ptr<Socket> socket, GameMonitor& gameMonitor, uint8_t id):
        id(id),
        socket(socket),
        sender(socket, std::ref(keepPlaying), std::ref(inGame), gameMonitor, id) {
    sender.start();
}

void Player::disconnect() {
    keepPlaying = false;
    inGame = false;
    socket->shutdown(SHUT_RDWR);
    socket->close();
    sender.stop();
    sender.join();
}

bool Player::isPlaying() const { return keepPlaying; }
