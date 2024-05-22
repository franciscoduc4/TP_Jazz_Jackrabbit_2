#include "lobby.h"
#include "ui_lobby.h"

Lobby::Lobby(QWidget *parent, const QString& playerName, Socket& skt) :
    QMainWindow(parent),
    ui(new Ui::Lobby),
    playerName(playerName),
    skt(skt)
{
    ui->setupUi(this);
}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::on_btnCreateGame_clicked()
{
    SceneSelection *ss = new SceneSelection(this->skt, this->playerName);
    ss->show();
    this->close();
}

