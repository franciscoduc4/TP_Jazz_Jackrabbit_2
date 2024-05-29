#ifndef RECEIVER_THREAD_H_
#define RECEIVER_THREAD_H_

#include "../../Common/Models/gameTypes.h"
#include "../../Common/protocol.h"
#include "../../Common/queue.h"
#include "../../Common/thread.h"
#include <memory>
\
class ReceiverThread: public Thread {
private:
    std::shared_ptr<Protocol> protocol;
    std::shared_ptr<Queue<GameTypes::Action>> gameQueue;

public:
    ReceiverThread(std::shared_ptr<Protocol> protocol,
                   std::shared_ptr<Queue<GameTypes::Action>> gameQueue);

    void run() override;
};

#endif  // RECEIVER_THREAD_H_
