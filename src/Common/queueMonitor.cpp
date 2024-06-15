#include "queueMonitor.h"

#include <algorithm>
#include <memory>
#include <string>
#include <utility>

#include "DTO/game.h"

template <typename T>
std::shared_ptr<Queue<T>> QueueMonitor<T>::createQueue(uint8_t id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto queue = std::make_shared<Queue<T>>();
    queues[id].push_back(queue);
    return queue;
}

template <typename T>
void QueueMonitor<T>::closeQueue(uint8_t id, std::shared_ptr<Queue<T>> queue) {
    std::lock_guard<std::mutex> lock(mtx);
    auto& vec = queues[id];
    auto it = std::find(vec.begin(), vec.end(), queue);
    if (it != vec.end()) {
        queue->close();
    }
}

template <typename T>
void QueueMonitor<T>::removeQueue(uint8_t id, std::shared_ptr<Queue<T>> queue) {
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
void QueueMonitor<T>::closeQueues(uint8_t id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto& vec = queues[id];
    for (auto& queue: vec) {
        queue->close();
    }
}

template <typename T>
void QueueMonitor<T>::removeQueues(uint8_t id) {
    std::lock_guard<std::mutex> lock(mtx);
    queues.erase(id);
}

template <typename T>
void QueueMonitor<T>::broadcast(uint8_t id, T&& event) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = queues.find(id);
    if (it != queues.end()) {
        auto& vec = it->second;
        for (auto& queue: vec) {
            if (queue) {
                queue->try_push(std::move(event));
            } else {
                std::cerr << "[QM] Warning: queue is null for id: " << id << std::endl;
            }
        }
    } else {
        std::cerr << "[QM] Warning: No queue found for id: " << id << std::endl;
    }
}


template <typename T>
void QueueMonitor<T>::assignGameIdToQueues(uint8_t gameId, std::shared_ptr<Queue<T>> queue) {
    std::lock_guard<std::mutex> lock(mtx);
    auto& vec = queues[gameId];
    if (!queue) {
        std::cerr << "[QM] Error: Trying to assign a null queue for gameId: " << gameId
                  << std::endl;
        return;
    }
    vec.push_back(queue);
    std::cout << "[QM] Assigned queue for gameId: " << gameId << std::endl;
}


// Especificaciones de instanciación para los tipos utilizados
template class QueueMonitor<std::string>;
template class QueueMonitor<std::unique_ptr<DTO>>;
