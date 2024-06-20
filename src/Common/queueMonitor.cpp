#include "queueMonitor.h"

#include <algorithm>
#include <memory>
#include <string>
#include <utility>

#include "DTO/command.h"
#include "DTO/game.h"

std::shared_ptr<Queue<std::unique_ptr<DTO>>> QueueMonitor::createQueue(uint8_t id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto queue = std::make_shared<Queue<std::unique_ptr<DTO>>>();
    queues[id].push_back(queue);
    return queue;
}

void QueueMonitor::closeQueue(uint8_t id, std::shared_ptr<Queue<std::unique_ptr<DTO>>> queue) {
    std::lock_guard<std::mutex> lock(mtx);
    auto& vec = queues[id];
    auto it = std::find(vec.begin(), vec.end(), queue);
    if (it != vec.end()) {
        queue->close();
    }
}

void QueueMonitor::removeQueue(uint8_t id, std::shared_ptr<Queue<std::unique_ptr<DTO>>> queue) {
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

void QueueMonitor::closeQueues(uint8_t id) {
    std::lock_guard<std::mutex> lock(mtx);
    auto& vec = queues[id];
    for (auto& queue: vec) {
        queue->close();
    }
}

void QueueMonitor::removeQueues(uint8_t id) {
    std::lock_guard<std::mutex> lock(mtx);
    queues.erase(id);
}

void QueueMonitor::broadcast(uint8_t id, const std::unique_ptr<DTO>& event) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = queues.find(id);
    if (it != queues.end()) {
        auto& vec = it->second;
        for (auto& queue: vec) {
            if (queue) {
                std::unique_ptr<DTO> eventCopy = event->clone();
                queue->try_push(std::move(eventCopy));
            } else {
                std::cerr << "[QM] Warning: queue is null for id: " << id << std::endl;
            }
        }
    } else {
        std::cerr << "[QM] Warning: No queue found for id: " << id << std::endl;
    }
}

void QueueMonitor::assignGameIdToQueues(uint8_t gameId, std::shared_ptr<Queue<std::unique_ptr<DTO>>> queue) {
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