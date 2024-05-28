#include "waitingroom.h"
#include "ui_waitingroom.h"

WaitingRoom::WaitingRoom(QWidget *parent,  QTMonitor& monitor, LobbyMessage& msg) :
    QMainWindow(parent),
    ui(new Ui::WaitingRoom),
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
    this->monitor.send_message(this->msg);
    QWidget* parent = this->parentWidget();
    if (parent){
        parent->show();
    }
    this->close();
} 

