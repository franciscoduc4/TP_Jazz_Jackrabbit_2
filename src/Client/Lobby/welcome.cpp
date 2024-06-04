#include "welcome.h"
#include "ui_welcome.h"

#include "lobby.h"

Welcome::Welcome(QWidget *parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame) :
    QMainWindow(parent),
    ui(new Ui::Welcome),
    client(client),
    msg(msg),
    clientJoinedGame(clientJoinedGame)
{
    ui->setupUi(this);
}

Welcome::~Welcome()
{
    delete ui;
}


void Welcome::on_btnIngresar_clicked()
{
    QString playerName = ui->inputName->text();

    if (playerName.isEmpty()) {
        QMessageBox::warning(this, "Ingrese su nombre para ingresar.");
        return;
    }

    this->msg.setPlayerName(playerName.toStdString());

    Lobby* lobby = new Lobby(this, this->client, this->msg, this->clientJoinedGame);
    lobby->show();
    this->close();
}

