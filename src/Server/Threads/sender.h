#ifndef SENDER_THREAD_H_
#define SENDER_THREAD_H_

#include <memory>
#include <string>

#include "../../Common/DTO/command.h"
#include "../../Common/DTO/game.h"
#include "../../Common/Models/gameTypes.h"
#include "../../Common/queue.h"
#include "../../Common/thread.h"
#include "../Game/gameMonitor.h"
#include "../Protocol/deserializer.h"
#include "../Protocol/serializer.h"

#include "receiver.h"

class SenderThread: public Thread {
private:
    int32_t playerId;
    Serializer serializer;
    Deserializer deserializer;
    std::atomic<bool>& keepPlaying;
    std::atomic<bool>& inGame;
    bool wasClosed;
    std::shared_ptr<Queue<GameDTO>> sendQueue;
    ReceiverThread receiver;
    GameMonitor& gameMonitor;
    std::shared_ptr<Queue<CommandDTO>> recvQueue;


public:
    SenderThread(std::shared_ptr<Socket> socket, std::atomic<bool>& keepPlaying,
                 std::atomic<bool>& inGame, GameMonitor& gameMonitor, int32_t id);

    void run() override;

    void runLobby();
};

#endif  // SENDER_THREAD_H_
