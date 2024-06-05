#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <memory>

#include "../Client/SDL/gamescreen.h"
#include "../Common/DTO/game.h"
#include "../Common/Types/command.h"
#include "../Common/socket.h"
#include "./Protocol/deserializer.h"
#include "./Protocol/serializer.h"
// #include "./Threads/cmdReaderThread.h"
#include "./Threads/receiverThread.h"
#include "./Threads/senderThread.h"
#include "Lobby/lobbyInit.h"

class Client {
private:
    char* ip;
    char* port;
    std::shared_ptr<Socket> skt;
    std::atomic<bool> was_closed;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>> senderQueue;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>> playerCmdsQueue;
    std::shared_ptr<Queue<std::unique_ptr<DTO>>> receiverQueue;
    SenderThread sender;
    Serializer serializer;
    // CmdReaderThread cmdReader;
    Deserializer deserializer;
    ReceiverThread receiver;


public:
    Client(char* ip, char* port);
    void start();
    std::unique_ptr<DTO> getServerMsg();
};

#endif  // CLIENT_H
