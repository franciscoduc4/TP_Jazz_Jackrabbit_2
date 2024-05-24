#include "waitingroom.h"
#include "ui_waitingroom.h"

WaitingRoom::WaitingRoom(QWidget *parent, SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg) :
    QMainWindow(parent),
    ui(new Ui::WaitingRoom),
    sender(sender),
    receiver(receiver),
    monitor(monitor),
    msg(msg)
{
    ui->setupUi(this);
}

WaitingRoom::~WaitingRoom()
{
    delete ui;
}

void WaitingRoom::on_btnBack_clicked()
{
    GameList* gl = new GameList(this->sender, this->receiver, this->monitor, this->msg);
    gl->show();
    this->close();
}

