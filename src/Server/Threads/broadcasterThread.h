#ifndef BRODCASTER_THREAD_H_
#define BRODCASTER_THREAD_H_

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "../../Common/Models/gameTypes.h"
#include "../../Common/queue.h"
#include "../../Common/queueMonitor.h"
#include "../../Common/thread.h"
#include "../Game/player.h"
#include "../Threads/senderThread.h"

class BroadcasterThread: public Thread {
private:
    std::shared_ptr<QueueMonitor<std::string>> queueMonitor;
    std::shared_ptr<Queue<std::string>>& sendQueue;

public:
    BroadcasterThread(std::shared_ptr<QueueMonitor<std::string>> queueMonitor,
                      std::shared_ptr<Queue<std::string>> sendQueue);
    void run();
    void stop();
};

#endif  // BRODCASTER_THREAD_H_
