#ifndef CLIENT_RECEIVER_THREAD_H
#define CLIENT_RECEIVER_THREAD_H

#include "../../Common/thread.h"
#include "../../Common/queue.h"
#include "../../Common/socket.h"
#include "../../Client/Protocol/deserializer.h"

#include <atomic>
#include <memory>
#include "../../Common/dtoValidator.h"

class ReceiverThread : public Thread {
private:
    Deserializer& deserializer;
    std::shared_ptr<Socket>& socket;
    std::atomic<bool>& was_closed;
    bool closed;

    void receiveGameDTO();

    void receiveLobbyDTO();
    void receiveGamesList();
    void receiveGameUpdate();
    void receiveCommandDTO();

public:
    ReceiverThread(Deserializer& deserializer, std::shared_ptr<Socket>& socket, std::atomic<bool>& was_closed);
    void run() override;

};

#endif  // CLIENT_RECEIVER_THREAD_H
