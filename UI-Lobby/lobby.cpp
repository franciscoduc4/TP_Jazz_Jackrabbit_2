#include "lobby.h"
#include "ui_lobby.h"

#include "../Common/Constants/lobbyCommands.h"

Lobby::Lobby(QWidget *parent,SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg) :
    QMainWindow(parent),
    ui(new Ui::Lobby),
    sender(sender),
    receiver(receiver),
    monitor(monitor),
    msg(msg)
{
    ui->setupUi(this);
}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::on_btnCreateGame_clicked()
{
    this->msg.setLobbyCmd(LobbyCommands::CREATE_GAME);
    SceneSelection* ss = new SceneSelection(this->sender, this->receiver, this->monitor, this->msg);
    ss->show();
    this->close();
}


void Lobby::on_btnJoinGame_clicked()
{
    this->msg.setLobbyCmd(LobbyCommands::JOIN_GAME);
    CharacterSelection* cs = new CharacterSelection(this->sender, this->receiver, this->monitor, this->msg);
    cs->show();
    this->close();
}


void Lobby::on_btnBack_clicked()
{
    this->msg.setLobbyCmd(LobbyCommands::INVALID_CMD);
    Welcome* w = new Welcome(this->sender, this->receiver, this->monitor, this->msg);
    w->show();
    this->close();
}

