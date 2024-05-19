#ifndef SENDER_THREAD_H_
#define SENDER_THREAD_H_

#include <memory>

#include "../../Common/gameTypes.h"
#include "../../Common/protocol.h"
#include "../../Common/queue.h"
#include "../../Common/thread.h"

class SenderThread: public Thread {
private:
    Protocol& protocol;
    std::shared_ptr<Queue<GameTypes::Event>> eventQueue;

public:
    SenderThread(Protocol& protocol, std::shared_ptr<Queue<GameTypes::Event>> eventQueue);

    void run() override;
};

#endif  // SENDER_THREAD_H_
