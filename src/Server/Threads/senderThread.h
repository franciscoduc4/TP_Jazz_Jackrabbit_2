#ifndef SENDER_THREAD_H_
#define SENDER_THREAD_H_

#include <memory>
#include <string>

#include "../../Common/Models/gameTypes.h"
#include "../../Common/queue.h"
#include "../../Common/thread.h"

class SenderThread: public Thread {
private:
    std::shared_ptr<Protocol> protocol;
    std::shared_ptr<Queue<std::string>> senderQueue;

public:
    SenderThread(std::shared_ptr<Protocol> protocol,
                 std::shared_ptr<Queue<std::string>> senderQueue);

    void run() override;
};

#endif  // SENDER_THREAD_H_
