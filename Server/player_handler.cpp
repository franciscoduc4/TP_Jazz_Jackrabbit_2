#include "player_handler.h"
#include "Common/protocol.h"
#include "Common/game_monitor.h"
#include "Common/queue.h"
#include "Common/socket.h"

PlayerHandler::PlayerHandler(Socket&& playerSocket, GameMonitor& gameMonitor, 
    std::shared_ptr<Queue<Action>>& actionQueue):

    protocol(std::move(playerSocket)), 
    gameMonitor(gameMonitor), 
    actionQueue(actionQueue),
    receiver(receiver),
    sender(protocol, gameQueue), 
    gameQueue(gameMonitor.getGameQueue()) {}

void PlayerHandler::run() {
    // gameMonitor.addPlayer();

    sender.start()
    receiver.start()    
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

bool PlayerHandler::isAlive() {
    return playerIsAlive;
}
