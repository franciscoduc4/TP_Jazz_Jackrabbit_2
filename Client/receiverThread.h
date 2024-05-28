#ifndef RECEIVERTHREAD_H
#define RECEIVERTHREAD_H

#include "../Common/thread.h"
#include "../Common/protocol.h"
#include "../Common/serializer.h"
#include "./gameStatusMonitor.h"
#include "../Client/lobbyMessage.h"

class ReceiverThread : public Thread {
 private:
    Protocol& protocol;
    Serializer serializer;
    GameStatusMonitor& monitor;
    bool inLobby;
 public:
   explicit ReceiverThread(Protocol& protocol, GameStatusMonitor& monitor);

   LobbyMessage receive_message();

   void run() override;
   
   ~ReceiverThread();
};

#endif  // RECEIVERTHREAD_H
