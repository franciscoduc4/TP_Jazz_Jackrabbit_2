#ifndef QUEUE_MANAGER_H
#define QUEUE_MANAGER_H

#include <algorithm>
#include <map>
#include <memory>
#include <mutex>
#include <vector>

#include "queue.h"

template <typename T>
class QueueMonitor {
private:
    std::map<uint8_t, std::vector<std::shared_ptr<Queue<T>>>> queues;
    std::mutex mtx;

public:
    std::shared_ptr<Queue<T>> createQueue(uint8_t id);
    void closeQueue(uint8_t id, std::shared_ptr<Queue<T>> queue);
    void removeQueue(uint8_t id, std::shared_ptr<Queue<T>> queue);
    void closeQueues(uint8_t id);
    void removeQueues(uint8_t id);
    void broadcast(uint8_t id, T&& event);
    void assignGameIdToQueues(uint8_t gameId, std::shared_ptr<Queue<T>> queue);
};

#endif  // QUEUE_MANAGER_H
