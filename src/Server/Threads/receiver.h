#ifndef RECEIVER_THREAD_H_
#define RECEIVER_THREAD_H_

#include <memory>

#include "../../Common/Models/gameTypes.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../../Common/thread.h"
#include "../Game/gameMonitor.h"

class ReceiverThread: public Thread {
private:
public:
    ReceiverThread(std::shared_ptr<Socket> socket, std::atomic<bool>& keepPlaying,
                   std::atomic<bool>& inGame, std::shared_ptr<Queue<CommandDTO>> recvQueue,
                   int32_t id);
    void run() override;
};

#endif  // RECEIVER_THREAD_H_
