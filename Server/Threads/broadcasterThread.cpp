#include "broadcasterThread.h"

BroadcasterThread::BroadcasterThread(): queueMonitor(), eventQueue(queueMonitor.createQueue()) {}

void BroadcasterThread::addSender(Player& player) {
    senderThreads.emplace(player.getId(), player.initSender(queueMonitor.createQueue()));
    senderThreads[player.getId()]->start();
}

void BroadcasterThread::removeSender(int playerId) {
    senderThreads[playerId]->stop();
    senderThreads[playerId]->join();
    senderThreads.erase(playerId);
}

void BroadcasterThread::run() {
    while (true) {
        GameTypes::Event event = eventQueue->pop();
        queueMonitor.broadcast(event);
    }
}
