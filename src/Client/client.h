#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <memory>

#include "../Common/DTO/game.h"
#include "../Common/Types/command.h"
#include "../Common/socket.h"
#include "./Protocol/deserializer.h"
#include "./Protocol/serializer.h"
#include "Lobby/lobbyInit.h"
#include "SDL/gamescreen.h"
#include "Threads/cmdReaderThread.h"
#include "Threads/receiverThread.h"
#include "Threads/senderThread.h"

class Client {
private:
    char* ip;
    char* port;
    std::shared_ptr<Socket> skt;
    std::atomic<bool> was_closed;
    std::shared_ptr<Queue<DTO>> senderQueue;
    std::shared_ptr<Queue<DTO>> playerCmdsQueue;
    std::shared_ptr<Queue<DTO>> receiverQueue;
    SenderThread sender;
    Serializer serializer;
    // CmdReaderThread cmdReader;
    Deserializer deserializer;
    ReceiverThread receiver;


public:
    Client(char* ip, char* port);
    void start();
    DTO getServerMsg();
};

#endif  // CLIENT_H
