#include <QApplication>

#include "../client.h"
#include "../Protocol/lobbyMessage.h"

#include "welcome.h"

int startQT(Client& client, int argc, char *argv[]) {
    LobbyMessage msg;
    QApplication a(argc, argv);
    Welcome w(client, &msg);
    w.show();
    return a.exec();
}
