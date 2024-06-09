#include <QApplication>

#include "../Protocol/Types/lobbyMessage.h"
#include "../client.h"

#include "welcome.h"

LobbyInit::LobbyInit() {}

bool LobbyInit::launchQT(LobbyController& controller, bool& clientJoinedGame) {
    LobbyMessage msg;

    int argc = 0;
    char arg1[] = "";
    char* argv[] = { arg1 };

    QApplication a(argc, argv);

    Welcome w(nullptr, controller, msg, clientJoinedGame);
    w.show();
    a.exec();

    return clientJoinedGame;
}
