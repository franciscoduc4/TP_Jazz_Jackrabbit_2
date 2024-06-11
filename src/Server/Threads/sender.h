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
    uint32_t playerId;
    Serializer serializer;
    Deserializer deserializer;
    std::atomic<bool>& keepPlaying;
    std::atomic<bool>& inGame;
    bool wasClosed;
    std::shared_ptr<Queue<std::unique_ptr<GameDTO>>> sendQueue;
    std::shared_ptr<Queue<std::unique_ptr<CommandDTO>>> recvQueue;
    ReceiverThread receiver;
    GameMonitor& gameMonitor;
    std::shared_ptr<Socket> socket;


public:
    SenderThread(std::shared_ptr<Socket> socket, std::atomic<bool>& keepPlaying,
                 std::atomic<bool>& inGame, GameMonitor& gameMonitor, uint32_t playerId,
                 std::shared_ptr<Queue<std::unique_ptr<GameDTO>>> sendQueue);

    void run() override;

    void runLobby(bool& wasClosed);
};

#endif  // SENDER_THREAD_H_
