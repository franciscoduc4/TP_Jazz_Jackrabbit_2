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
        playerCmdsQueue(std::make_shared<Queue<DTO>>()),
        sender(this->skt, this->senderQueue, this->was_closed),
        serializer(this->sender),
        cmdReader(this->serializer, this->playerCmdsQueue),
        deserializer(),
        receiver(this->skt, this->deserializer){
    this->sender.start();
    this->receiver.start();
    this->cmdReader.start();
}

void Client::start() {
    bool clientJoinedGame = false;
    do {
        LobbyInit init;
        clientJoinedGame = init.launchQT(this);

        if (!clientJoinedGame) {
            break;
        }

        // TODO: Continue with SDL.

    } while (clientJoinedGame);
}
