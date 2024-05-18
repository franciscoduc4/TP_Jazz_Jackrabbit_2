#ifndef SERVER_CLIENT_RECEIVER_H
#define SERVER_CLIENT_RECEIVER_H

#include "../Common/gameTypes.h"
#include "../Common/queue.h"
#include "../Common/thread.h"

#include "protocol.h"


class ReceiverThread: public Thread {
private:
    Protocol& protocol;
    Queue<GameTypes::Action>& gameQueue;

public:
    ReceiverThread(Protocol& protocol, Queue<GameTypes::Action>& gameQueue);

    void run() override;
};

#endif  // SERVER_CLIENT_RECEIVER_H
