#ifndef SERVER_CLIENT_SENDER_H
#define SERVER_CLIENT_SENDER_H

#include <memory>

#include "../Common/gameTypes.h"
#include "../Common/queue.h"
#include "../Common/thread.h"

#include "protocol.h"

class ClientSender: public Thread {
private:
    Protocol& protocol;
    std::shared_ptr<Queue<GameTypes::Event>> eventQueue;

public:
    ClientSender(Protocol& protocol, std::shared_ptr<Queue<GameTypes::Event>> eventQueue);

    void run() override;
};

#endif  // SERVER_CLIENT_SENDER_H