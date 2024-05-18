#ifndef BRODCASTER_THREAD_H_
#define BRODCASTER_THREAD_H_

#include <map>
#include <memory>

#include "../Common/gameTypes.h"
#include "../Common/queue.h"
#include "../Common/thread.h"
#include "../Game/player.h"
#include "../Game/queueMonitor.h"
#include "../Threads/senderThread.h"

class BroadcasterThread: public Thread {
private:
    QueueMonitor queueMonitor;
    std::shared_ptr<Queue<GameTypes::Event>> eventQueue;
    std::map<int, std::shared_ptr<SenderThread>> senderThreads;

public:
    BroadcasterThread();
    void addSender(Player& player);
    void removeSender(int playerId);
    void run();
    void stop();
    ~BroadcasterThread();
};

#endif  // BRODCASTER_THREAD_H_