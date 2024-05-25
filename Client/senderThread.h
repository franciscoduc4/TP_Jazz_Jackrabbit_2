#include "../Common/socket.h"
#include "../Common/thread.h"
#include "../Common/queue.h"
#include "../Common/protocol.h"

class SenderThread: public Thread {
private:
    Protocol& protocol;
    Socket& socket;
    Queue& cmdsQueue;

public:
    explicit SenderThread(Protocol& p, Socket& skt, Queue& cmdsQueue);

    void push_message(const ProtocolMessage& msg);

    void run() override;

    ~SenderThread();


}
