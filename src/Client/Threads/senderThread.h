#ifndef CLIENT_SENDER_THREAD_H
#define CLIENT_SENDER_THREAD_H

#include "../../Common/thread.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../../Common/DTO/dto.h"
#include <atomic>
#include <memory>

class SenderThread : public Thread {
private:
    std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue;
    std::shared_ptr<Socket>& socket;
    std::atomic<bool>& was_closed;
    bool closed;
public:
    SenderThread(std::shared_ptr<Queue<std::unique_ptr<DTO>>>& queue, std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed);
    void run() override;
    ~SenderThread();
};

#endif  // CLIENT_SENDER_THREAD_H
