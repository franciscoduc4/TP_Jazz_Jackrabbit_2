#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include <QDialog>

#include "../../Common/Types/lobbyMessage.h"
#include "../client.h"

namespace Ui {
class WaitingRoom;
}

class WaitingRoom : public QDialog
{
    Q_OBJECT
    


public:
    explicit WaitingRoom(QWidget *parent, LobbyController& controller, LobbyMessage& msg, bool& clientJoinedGame);
    ~WaitingRoom();

private:
    Ui::WaitingRoom *ui;
    LobbyController& controller;
    LobbyMessage& msg;
    bool& clientJoinedGame;
};

#endif // WAITINGROOM_H
