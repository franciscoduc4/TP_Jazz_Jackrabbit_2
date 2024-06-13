#ifndef QUEUE_MANAGER_H
#define QUEUE_MANAGER_H

#include <algorithm>
#include <memory>
#include <mutex>
#include <vector>
#include <map>
#include "queue.h"

template <typename T>
class QueueMonitor {
private:
    std::map<uint32_t, std::vector<std::shared_ptr<Queue<T>>>> queues;
    std::mutex mtx;

public:
    std::shared_ptr<Queue<T>> createQueue(uint32_t id);
    void closeQueue(uint32_t id, std::shared_ptr<Queue<T>> queue);
    void removeQueue(uint32_t id, std::shared_ptr<Queue<T>> queue);
    void closeQueues(uint32_t id);
    void removeQueues(uint32_t id);
    void broadcast(uint32_t id, T&& event);
    void assignGameIdToQueues(uint32_t gameId, std::shared_ptr<Queue<T>> queue);
};

#endif  // QUEUE_MANAGER_H
