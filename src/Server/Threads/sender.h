#ifndef SENDER_THREAD_H_
#define SENDER_THREAD_H_

#include <memory>
#include <string>

#include "../../Common/DTO/command.h"
#include "../../Common/DTO/game.h"
#include "../../Common/queue.h"
#include "../../Common/queueMonitor.h"
#include "../../Common/thread.h"
#include "../Game/gameMonitor.h"
#include "../Protocol/deserializer.h"
#include "../Protocol/serializer.h"

#include "receiver.h"

class SenderThread: public Thread {
private:
    std::shared_ptr<Socket> socket;
    std::atomic<bool>& keepPlaying;
    std::atomic<bool>& inGame;
    uint8_t playerId;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>> sendQueue;
    Serializer serializer;
    Deserializer deserializer;


public:
    SenderThread(const std::shared_ptr<Socket>& socket, std::atomic<bool>& keepPlaying,
                 std::atomic<bool>& inGame, uint8_t playerId,
                 const std::shared_ptr<Queue<std::unique_ptr<DTO>>>& sendQueue);

    void run() override;

    void runLobby();
};

#endif  // SENDER_THREAD_H_
