#include "../Common/socket.h"
#include "../Common/thread.h"
#include "../Common/protocol.h"
#include "../Common/messageSerializer.h"
#include "../Common/logger.h"

class ReceiverThread : public Thread {
 private:
    Socket& socket;
    Protocol& protocol;
    MessageSerializer serializer;
    Logger& logger;
 public:
    ReceiverThread(Socket& socket, Protocol& protocol);

    void run() override;
    
    ~ReceiverThread();
}
