#ifndef SERVER_QUEUE_MANAGER_H
#define SERVER_QUEUE_MANAGER_H

#include <algorithm>
#include <memory>
#include <mutex>
#include <vector>

#include "../../Common/gameTypes.h"
#include "../../Common/protocol.h"
#include "../../Common/queue.h"

class QueueMonitor {
private:
    std::vector<std::shared_ptr<Queue<GameTypes::Event>>> queues;
    std::mutex mtx;

public:
    QueueMonitor() = default;
    ~QueueMonitor() { removeQueues(); }

    std::shared_ptr<Queue<GameTypes::Event>> createQueue();

    void closeQueue(std::shared_ptr<Queue<GameTypes::Event>> queue);

    void removeQueue(std::shared_ptr<Queue<GameTypes::Event>> queue);

    void closeQueues();

    void removeQueues();

    void broadcast(const GameTypes::Event& events);

    QueueMonitor(const QueueMonitor&) = delete;
    QueueMonitor& operator=(const QueueMonitor&) = delete;
};

#endif  // SERVER_QUEUE_MANAGER_H
