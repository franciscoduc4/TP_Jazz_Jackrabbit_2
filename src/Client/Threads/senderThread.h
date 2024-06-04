#ifndef CLIENT_SENDER_THREAD_H
#define CLIENT_SENDER_THREAD_H

#include "../../Common/thread.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include <atomic>
#include <memory>

class SenderThread : public Thread {
private:
    std::shared_ptr<Queue<DTO>>& queue;
    std::shared_ptr<Socket>& socket;
    std::atomic<bool>& was_closed;
    bool closed;
public:
    SenderThread(std::shared_ptr<Queue<DTO>>& queue, Socket& socket, std::atomic<bool>& was_closed);
    void run() override;
    void stop();
    ~SenderThread();
};

#endif  // CLIENT_SENDER_THREAD_H
