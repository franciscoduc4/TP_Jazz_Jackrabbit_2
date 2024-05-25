#include "./client.h"
#include "../Common/socket.h"
#include "../Common/queue.h"
#include "../Common/protocol.h"
#include "./senderThread.h"
#include "./receiverThread.h"
#include "./QTMonitor.h"
#include "Lobby/init.h"


Client::Client(char* ip, char* port) : ip(ip), port(port) {}

void Client::start() {
    bool runApp = false;
    do {
        Socket skt(ip, port);
        Protocol protocol(std::move(skt));
        Queue cmdQueue;
        SenderThread sender(protocol, &skt, &cmdQueue);
        sender.start();
        ReceiverThread receiver(protocol, &skt);
        receiver.start();
        QTMonitor monitor(&protocol, &sender, &receiver);

        LobbyInit init(&sender, &receiver, &monitor);
        init.run();

        // TODO: Ver cómo salir de QT y arrancar SDL.
    } while (runApp);
}
