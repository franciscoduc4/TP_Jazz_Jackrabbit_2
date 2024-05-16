#include "playerHandler.h"


PlayerHandler::PlayerHandler(Socket&& playerSocket, GamesMonitor& gameMonitor,
                             std::shared_ptr<Queue<GameTypes::Action>>& actionQueue):

        protocol(std::move(playerSocket)),
        gamesMonitor(gamesMonitor),
        actionQueue(actionQueue),
        gameQueue(gameMonitor.getGameQueue()),
        receiver(receiver, gameQueue),
        sender(protocol) {}

void PlayerHandler::run() {
    // gameMonitor.addPlayer();

    sender.start() receiver.start()
}

void PlayerHandler::stop() {
    // gameMonitor.removePlayer();
    sender.stop();
    receiver.stop();
}

void PlayerHandler::join() {
    sender.join();
    receiver.join();
}

bool PlayerHandler::isAlive() { return playerIsAlive; }
