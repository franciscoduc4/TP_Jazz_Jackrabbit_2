#include "queueMonitor.h"


std::shared_ptr<Queue<GameTypes::Event>> QueueMonitor::createQueue() {
    std::lock_guard<std::mutex> lock(mtx);
    auto queue = std::make_shared<Queue<GameTypes::Event>>();
    queues.push_back(queue);
    return queue;
}

void QueueMonitor::closeQueue(std::shared_ptr<Queue<GameTypes::Event>> queue) {
    std::lock_guard<std::mutex> lock(mtx);
    queue->close();
}

void QueueMonitor::removeQueue(std::shared_ptr<Queue<GameTypes::Event>> queue) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = std::find(queues.begin(), queues.end(), queue);
    if (it != queues.end()) {
        queues.erase(it);
    }
}

void QueueMonitor::closeQueues() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& queue: queues) {
        queue->close();
    }
}

void QueueMonitor::removeQueues() {
    std::lock_guard<std::mutex> lock(mtx);
    queues.clear();
}

void QueueMonitor::broadcast(const GameTypes::Event& events) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& queue: queues) {
        queue->try_push(events);
    }
}
