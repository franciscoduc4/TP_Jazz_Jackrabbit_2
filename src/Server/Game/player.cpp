#include "player.h"

#include <sys/socket.h>

#include "../Physics/character.h"

Player::Player(std::shared_ptr<Socket> socket, GameMonitor& gameMonitor,
               QueueMonitor<std::shared_ptr<Queue<GameDTO>>>& queueMonitor, int32_t playerId):
        playerId(playerId),
        socket(socket),
        sender(socket, std::ref(keepPlaying), std::ref(inGame), gameMonitor, playerId,
               queueMonitor.createQueue()) {
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
