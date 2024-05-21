#ifndef RECEIVER_THREAD_H_
#define RECEIVER_THREAD_H_

#include "../../Common/Models/gameTypes.h"
#include "../../Common/protocol.h"
#include "../../Common/queue.h"
#include "../../Common/thread.h"

class ReceiverThread: public Thread {
private:
    Protocol protocol;
    Queue<GameTypes::Action>& gameQueue;

public:
    ReceiverThread(Protocol& protocol, Queue<GameTypes::Action>& gameQueue);

    void run() override;
};

#endif  // RECEIVER_THREAD_H_
