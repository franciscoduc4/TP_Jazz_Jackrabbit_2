#include "broadcasterThread.h"


BroadcasterThread::BroadcasterThread(): queueMonitor(), snapshotQueue(queueMonitor.createQueue()) {}

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
        std::string snapshot = snapshotQueue->pop();
        queueMonitor.broadcast(snapshot);
    }
}
