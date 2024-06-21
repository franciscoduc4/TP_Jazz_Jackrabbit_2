#include <QApplication>
#include <utility>

#include "statistics.h"
#include "welcome.h"

LobbyInit::LobbyInit() {}

std::pair<bool, LobbyMessage> LobbyInit::launchQT(LobbyController& controller, bool& clientJoinedGame) {
    LobbyMessage msg;

    int argc = 0;
    char arg1[] = "";
    char* argv[] = { arg1 };

    QApplication a(argc, argv);

    Welcome w(nullptr, controller, msg, clientJoinedGame);
    w.show();
    int exitCode = a.exec();

    if (exitCode == 37) return std::make_pair(false, msg);

    return std::make_pair(clientJoinedGame, msg);
}

void LobbyInit::displayStats(FinalStats stats, bool& clientJoinedGame) {
    int argc = 0;
    char arg1[] = "";
    char* argv[] = { arg1 };

    QApplication a(argc, argv);

    Statistics s(nullptr, std::move(stats), clientJoinedGame);
    s.show();
    a.exec();
}