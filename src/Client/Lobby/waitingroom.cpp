#include "waitingroom.h"
#include "ui_waitingroom.h"

WaitingRoom::WaitingRoom(QWidget *parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame) :
    QDialog (parent),
    ui(new Ui::WaitingRoom),
    client(client),
    msg(msg),
    clientJoinedGame(clientJoinedGame)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

WaitingRoom::~WaitingRoom()
{
    delete ui;
}

void WaitingRoom::on_btnBack_clicked() {
    // Do Something.
}

