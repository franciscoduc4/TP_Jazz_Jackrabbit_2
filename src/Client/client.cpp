#include "./client.h"
#include "../Common/socket.h"
#include "./Threads/senderThread.h"
#include "./Threads/receiverThread.h"
#include "./Threads/cmdReaderThread.h"
#include "./Protocol/serializer.h"
#include "./Protocol/deserializer.h"
#include "Lobby/lobbyInit.h"


Client::Client(char* ip, char* port) :
        ip(ip),
        port(port),
        skt(std::make_shared<Socket>(ip, port)),
        was_closed(false),
        senderQueue(std::make_shared<Queue<DTO>>()),
        sender(this->skt, this->senderQueue, this->was_closed),
        serializer(this->sender),
        cmdReader(this->serializer),
        deserializer(),
        receiver(this->skt, this->deserializer){}

void Client::start(int argc, char *argv[]) {
    bool runApp = false;
    do {
        LobbyInit init;
        init.startQT(this, argc, argv);

    } while (runApp);
}
