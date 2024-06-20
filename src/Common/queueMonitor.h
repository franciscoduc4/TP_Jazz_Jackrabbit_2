#ifndef QUEUE_MANAGER_H
#define QUEUE_MANAGER_H

#include <algorithm>
#include <map>
#include <memory>
#include <mutex>
#include <vector>

#include "queue.h"
#include "DTO/dto.h"

class QueueMonitor {
private:
    std::map<uint8_t, std::vector<std::shared_ptr<Queue<std::unique_ptr<DTO>>>>> queues;
    std::mutex mtx;

public:
    std::shared_ptr<Queue<std::unique_ptr<DTO>>> createQueue(uint8_t id);
    void closeQueue(uint8_t id, const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue);
    void removeQueue(uint8_t id, const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue);
    void closeQueues(uint8_t id);
    void removeQueues(uint8_t id);
    void broadcast(uint8_t id, const std::unique_ptr<DTO>& event);
    void assignGameIdToQueues(uint8_t gameId, const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue);
};

#endif  // QUEUE_MANAGER_H
