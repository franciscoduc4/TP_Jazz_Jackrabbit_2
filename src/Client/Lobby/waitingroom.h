#ifndef WAITINGROOM_H
#define WAITINGROOM_H

#include <QMainWindow>

#include "../client.h"
#include "../Protocol/Types/lobbyMessage.h"

namespace Ui {
class WaitingRoom;
}

class WaitingRoom : public QMainWindow
{
    Q_OBJECT
    


public:
    explicit WaitingRoom(QWidget *parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame);
    ~WaitingRoom();

private slots:
    void on_btnBack_clicked();

private:
    Ui::WaitingRoom *ui;
    Client& client;
    LobbyMessage& msg;
    bool& clientJoinedGame;
};

#endif // WAITINGROOM_H
