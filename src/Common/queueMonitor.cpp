#include "queueMonitor.h"
#include <string>
#include <memory>
#include <algorithm>
#include <utility>
#include "DTO/game.h"

template <typename T>
std::shared_ptr<Queue<T>> QueueMonitor<T>::createQueue(uint32_t id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto queue = std::make_shared<Queue<T>>();
    queues[id].push_back(queue);
    return queue;
}

template <typename T>
void QueueMonitor<T>::closeQueue(uint32_t id, std::shared_ptr<Queue<T>> queue) {
    std::lock_guard<std::mutex> lock(mtx);
    auto& vec = queues[id];
    auto it = std::find(vec.begin(), vec.end(), queue);
    if (it != vec.end()) {
        queue->close();
    }
}

template <typename T>
void QueueMonitor<T>::removeQueue(uint32_t id, std::shared_ptr<Queue<T>> queue) {
    std::lock_guard<std::mutex> lock(mtx);
    auto& vec = queues[id];
    auto it = std::find(vec.begin(), vec.end(), queue);
    if (it != vec.end()) {
        vec.erase(it);
        if (vec.empty()) {
            queues.erase(id);
        }
    }
}

template <typename T>
void QueueMonitor<T>::closeQueues(uint32_t id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto& vec = queues[id];
    for (auto& queue: vec) {
        queue->close();
    }
}

template <typename T>
void QueueMonitor<T>::removeQueues(uint32_t id) {
    std::lock_guard<std::mutex> lock(mtx);
    queues.erase(id);
}

template <typename T>
void QueueMonitor<T>::broadcast(uint32_t id, T&& event) {
    std::lock_guard<std::mutex> lock(mtx);
    auto& vec = queues[id];
    for (auto& queue: vec) {
        queue->try_push(std::move(event));
    }
}

template <typename T>
void QueueMonitor<T>::assignGameIdToQueues(uint32_t gameId, std::shared_ptr<Queue<T>> queue) {
    std::lock_guard<std::mutex> lock(mtx);
    queues[gameId].push_back(queue);
}


// Especificaciones de instanciación para los tipos utilizados
template class QueueMonitor<std::string>;
template class QueueMonitor<std::unique_ptr<GameDTO>>;
