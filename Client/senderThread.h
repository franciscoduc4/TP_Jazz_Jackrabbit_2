#ifndef SENDERTHREAD_H
#define SENDERTHREAD_H

#include "../Common/protocol.h"
#include "../Common/thread.h"
#include "../Common/queue.h"
#include "./gameStatusMonitor.h"

class SenderThread : public Thread {
private:
    Protocol& protocol;
    Queue<ProtocolMessage>& cmdsQueue;
    GameStatusMonitor& gameMonitor;

public:
    SenderThread(
        Protocol& protocol,
        Queue<ProtocolMessage>& cmdsQueue,
        GameStatusMonitor& gameMonitor);

    void push_message(const ProtocolMessage& msg);

    void run() override;

    ~SenderThread();


};

#endif  // SENDERTHREAD_H
