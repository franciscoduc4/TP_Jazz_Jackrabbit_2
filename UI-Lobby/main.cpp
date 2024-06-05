#include <QApplication>

#include "../Client/receiverThread.h"
#include "../Client/senderThread.h"
#include "../Common/protocol.h"
#include "../Common/queue.h"
#include "../Common/socket.h"
#include "../src/Client/Monitors/QTMonitor.h"
#include "../src/Client/Protocol/lobbyMessage.h"

#include "welcome.h"

int main(int argc, char *argv[])
{
    char* ip = "127.0.0.1";
    char* port = "8080";
    Socket skt(ip, port);
    Protocol protocol(std::move(skt));
    Queue<ProtocolMessage> cmdQueue;
    SenderThread sender(protocol, &skt, &cmdQueue);
    sender.start();
    ReceiverThread receiver(&skt, &protocol);
    receiver.start();
    LobbyMessage msg;
    QTMonitor monitor(&protocol, &sender, &receiver);
    QApplication a(argc, argv);
    Welcome w(&sender, &receiver, &monitor, &msg);
    w.show();
    return a.exec();
}
