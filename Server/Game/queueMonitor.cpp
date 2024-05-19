#include "queueMonitor.h"

template <typename T>
std::shared_ptr<Queue<T>> QueueMonitor<T>::createQueue() {
    std::lock_guard<std::mutex> lock(mtx);
    auto queue = std::make_shared<Queue<T>>();
    queues.push_back(queue);
    return queue;
}

template <typename T>
void QueueMonitor<T>::closeQueue(std::shared_ptr<Queue<T>> queue) {
    std::lock_guard<std::mutex> lock(mtx);
    queue->close();
}

template <typename T>
void QueueMonitor<T>::removeQueue(std::shared_ptr<Queue<T>> queue) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = std::find(queues.begin(), queues.end(), queue);
    if (it != queues.end()) {
        queues.erase(it);
    }
}

template <typename T>
void QueueMonitor<T>::closeQueues() {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& queue: queues) {
        queue->close();
    }
}

template <typename T>
void QueueMonitor<T>::removeQueues() {
    std::lock_guard<std::mutex> lock(mtx);
    queues.clear();
}

template <typename T>
void QueueMonitor<T>::broadcast(const T& event) {
    std::lock_guard<std::mutex> lock(mtx);
    for (auto& queue: queues) {
        queue->try_push(event);
    }
}
