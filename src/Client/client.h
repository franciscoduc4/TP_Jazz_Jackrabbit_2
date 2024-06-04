#ifndef CLIENT_H
#define CLIENT_H

#include <memory>
#include <atomic>

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
