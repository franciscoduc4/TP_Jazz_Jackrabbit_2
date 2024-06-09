#include "waitingroom.h"
#include "ui_waitingroom.h"

WaitingRoom::WaitingRoom(QWidget *parent, LobbyController& controller, LobbyMessage& msg, bool& clientJoinedGame) :
    QDialog (parent),
    ui(new Ui::WaitingRoom),
    controller(controller),
    msg(msg),
    clientJoinedGame(clientJoinedGame)
{
    ui->setupUi(this);
}

WaitingRoom::~WaitingRoom()
{
    delete ui;
}

void WaitingRoom::on_btnBack_clicked() {
     this->hide();

     QWidget* parent = this->parentWidget();
     if (parent) {
         parent->show();
     }

     this->close();
}

