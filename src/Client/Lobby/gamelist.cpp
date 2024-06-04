#include "gamelist.h"
#include "ui_gamelist.h"

#include "waitingroom.h"

GameList::GameList(QWidget *parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame) :
    QMainWindow(parent),
    ui(new Ui::GameList),
    client(client),
    msg(msg),
    clientJoinedGame(clientJoinedGame)
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

    bool joinResult = this->client.sendLobbyMessage(this->msg);

    if (joinResult) {
        this->clientJoinedGame = true;
        WaitingRoom* wr = new WaitingRoom(this, this->client, this->msg, this->clientJoinedGame);
        wr->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Error al unirse a la partida.", "Error");
    }
}


void GameList::on_btnBack_clicked()
{
    this->setGameName("");
    QWidget* parent = this->parentWidget();
    if (parent){
        parent->show();
    }
    this->close();
}

