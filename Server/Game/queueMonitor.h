#ifndef SERVER_QUEUE_MANAGER_H
#define SERVER_QUEUE_MANAGER_H

#include <algorithm>
#include <memory>
#include <mutex>
#include <vector>

#include "../../Common/gameTypes.h"
#include "../../Common/protocol.h"
#include "../../Common/queue.h"


template <typename T>
class QueueMonitor {
public:
    std::shared_ptr<Queue<T>> createQueue();
    void closeQueue(std::shared_ptr<Queue<T>> queue);
    void removeQueue(std::shared_ptr<Queue<T>> queue);
    void closeQueues();
    void removeQueues();
    void broadcast(const T& event);

private:
    std::vector<std::shared_ptr<Queue<T>>> queues;
    std::mutex mtx;
};


#endif  // SERVER_QUEUE_MANAGER_H
