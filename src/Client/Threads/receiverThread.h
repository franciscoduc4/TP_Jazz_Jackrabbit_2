#ifndef CLIENT_RECEIVER_THREAD_H
#define CLIENT_RECEIVER_THREAD_H

#include "../../Common/thread.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include <atomic>
#include <memory>

class ReceiverThread : public Thread {
private:
    Deserializer& deserializer;
    std::shared_ptr<Socket>& socket;
    std::atomic<bool>& was_closed;
    bool closed;

public:
    ReceiverThread(Deserializer& deserializer, std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed);
    void run() override;
    ~ReceiverThread();

};

#endif  // CLIENT_RECEIVER_THREAD_H
