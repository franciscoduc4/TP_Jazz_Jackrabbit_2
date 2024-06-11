#include "player.h"

#include <sys/socket.h>


Player::Player(std::shared_ptr<Socket> socket, GameMonitor& gameMonitor,
               QueueMonitor<std::unique_ptr<GameDTO>>& queueMonitor, uint32_t playerId):
        playerId(playerId),
        socket(socket),
        sender(socket, std::ref(keepPlaying), std::ref(inGame), gameMonitor, playerId,
               std::shared_ptr<Queue<std::unique_ptr<GameDTO>>>()) {
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
