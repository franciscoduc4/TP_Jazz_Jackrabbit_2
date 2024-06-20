#ifndef RECEIVER_THREAD_H_
#define RECEIVER_THREAD_H_

#include <memory>

#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../../Common/thread.h"
#include "../Game/gameMonitor.h"
#include "../Protocol/deserializer.h"
#include "../Protocol/serializer.h"

class ReceiverThread: public Thread {
private:
    uint8_t playerId;
    Serializer serializer;
    Deserializer deserializer;
    std::atomic<bool>& keepPlaying;
    std::atomic<bool>& inGame;
    std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue;

    void runGame();

public:
    ReceiverThread(const std::shared_ptr<Socket>& socket, std::atomic<bool>& keepPlaying,
                   std::atomic<bool>& inGame, uint8_t playerId,
                   const std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>>& recvQueue);
    void run() override;
};

#endif  // RECEIVER_THREAD_H_
