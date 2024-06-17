#ifndef CLIENT_RECEIVER_THREAD_H
#define CLIENT_RECEIVER_THREAD_H

#include <atomic>
#include <memory>
#include <unordered_map>

#include <netinet/in.h>

#include "../../Client/Protocol/deserializer.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../../Common/thread.h"
#include "../Protocol/protocol.h"

class ReceiverThread : public Thread {
private:
    Deserializer& deserializer;
    std::shared_ptr<Socket>& socket;
    std::atomic<bool>& was_closed;
    ClientProtocol protocol;

    void receiveDTOByType(const char& dtoType);

public:
    ReceiverThread(Deserializer& deserializer, std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed);
    void run() override;

};

#endif  // CLIENT_RECEIVER_THREAD_H
