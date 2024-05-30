#ifndef QUEUE_MANAGER_H
#define QUEUE_MANAGER_H

#include <algorithm>
#include <memory>
#include <mutex>
#include <vector>

#include "queue.h"

template <typename T>
class QueueMonitor {
private:
    std::vector<std::shared_ptr<Queue<T>>> queues;
    std::mutex mtx;

public:
    std::shared_ptr<Queue<T>> createQueue();
    void closeQueue(std::shared_ptr<Queue<T>> queue);
    void removeQueue(std::shared_ptr<Queue<T>> queue);
    void closeQueues();
    void removeQueues();
    void broadcast(const T& event);
};


#endif  // QUEUE_MANAGER_H
