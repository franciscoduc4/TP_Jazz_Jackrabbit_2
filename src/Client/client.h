#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include <atomic>
#include "../Common/socket.h"
#include "Threads/senderThread.h"
#include "Threads/receiverThread.h"
#include "Threads/cmdReaderThread.h"
#include "./Protocol/serializer.h"
#include "./Protocol/deserializer.h"
#include "Lobby/lobbyInit.h"

#include "SDL/gamescreen.h"
#include "../Common/DTO/game.h"
#include "../Common/Types/command.h"

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
        CmdReaderThread cmdReader;
        Deserializer deserializer;
        ReceiverThread receiver;


    public:
        Client(char* ip, char* port);
        void start();
        DTO getServerMsg();
};

#endif  // CLIENT_H
