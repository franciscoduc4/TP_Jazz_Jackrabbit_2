#include "gamelist.h"
#include "ui_gamelist.h"

#include "waitingroom.h"

GameList::GameList(QWidget *parent, QTMonitor& monitor, LobbyMessage& msg) :
    QMainWindow(parent),
    ui(new Ui::GameList),
    monitor(monitor),
    msg(msg)
{
    ui->setupUi(this);
}

GameList::~GameList()
{
    delete ui;
}

void GameList::on_btnJoin_clicked()
{
    //ui->
    //this->msg.setGameName(nombrePartida.toStdString());
    this->monitor.send_message(this->msg.toString());

    WaitingRoom* wr = new WaitingRoom(this, this->monitor, this->msg);
    wr->show();
    this->close();
}


void GameList::on_btnBack_clicked()
{
    this->msg.setGameName("");
    QWidget* parent = this->parentWidget();
    if (parent){
        parent->show();
    }
    this->close();
}

