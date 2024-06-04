#include "waitingroom.h"
#include "ui_waitingroom.h"

WaitingRoom::WaitingRoom(QWidget *parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame) :
    QMainWindow(parent),
    ui(new Ui::WaitingRoom),
    client(client),
    msg(msg),
    clientJoinedGame(clientJoinedGame)
{
    ui->setupUi(this);
}

WaitingRoom::~WaitingRoom()
{
    delete ui;
}

