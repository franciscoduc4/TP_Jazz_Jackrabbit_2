#include "broadcasterThread.h"


BroadcasterThread::BroadcasterThread(std::shared_ptr<QueueMonitor<std::string>> queueMonitor,
                                     std::shared_ptr<Queue<std::string>> sendQueue):
        queueMonitor(queueMonitor), sendQueue(sendQueue) {}


void BroadcasterThread::run() {
    while (true) {
        std::string snapshot = sendQueue->pop();
        queueMonitor->broadcast(snapshot);
    }
}

void BroadcasterThread::stop() { sendQueue->close(); }
