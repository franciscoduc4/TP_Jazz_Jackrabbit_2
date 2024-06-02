#include "welcome.h"

#include <QApplication>

#include "../Client/QTMonitor.h"
#include "../Client/gameStatusMonitor.h"
#include "../Client/senderThread.h"
#include "../Client/receiverThread.h"
#include "../Common/protocol.h"
#include "../Common/socket.h"
#include "../Common/queue.h"
#include "../Client/lobbyMessage.h"
#include "./welcome.h"

int main(int argc, char *argv[])
{
    char* ip = "127.0.0.1";
    char* port = "8080";
    Socket skt(ip, port);
    Protocol protocol(std::move(skt));
    Queue<ProtocolMessage> cmdQueue;
    GameStatusMonitor gameMonitor;
    SenderThread sender(protocol, cmdQueue, gameMonitor);
    sender.start();
    ReceiverThread receiver(protocol, gameMonitor);
    receiver.start();
    LobbyMessage msg;
    QTMonitor qtMonitor(sender, receiver);
    QApplication a(argc, argv);
    Welcome w(nullptr, qtMonitor, msg);
    w.show();
    return a.exec();
}
