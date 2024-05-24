#include "gamelist.h"
#include "ui_gamelist.h"

GameList::GameList(QWidget *parent, SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg) :
    QMainWindow(parent),
    ui(new Ui::GameList),
    sender(sender),
    receiver(receiver),
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
    this->msg.setGameName(nombrePartida.toStdString());
    this->sender.sendMessage(this->msg);
}


void GameList::on_btnBack_clicked()
{
    this->setGameName("");
    CharacterSelection* cs = new CharacterSelection(this->sender, this->receiver, this->monitor, this->msg);
    cs->show();
    this->close();
}

