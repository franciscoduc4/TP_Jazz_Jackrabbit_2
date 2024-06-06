#include "creategame.h"

#include <QMessageBox>

#include "characterselection.h"
#include "ui_creategame.h"

CreateGame::CreateGame(QWidget* parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame):
        QDialog(parent),
        ui(new Ui::CreateGame),
        client(client),
        msg(msg),
        clientJoinedGame(clientJoinedGame) {
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

CreateGame::~CreateGame() { delete ui; }

void CreateGame::on_btnCreate_clicked() {
    QString gameName = ui->gameName->text();
    int numPlayers = ui->numPlayers->value();
    int waitTime = ui->waitTime->value();

    if (gameName.isEmpty()) {
        QMessageBox::warning(this, "Ingrese un nombre para la partida", "Error");
        return;
    }
    this->msg.setGameName(gameName.toStdString());
    this->msg.setMaxPlayers(numPlayers);
    this->msg.setWaitTime(waitTime);

    CharacterSelection* cs =
            new CharacterSelection(this, this->client, this->msg, this->clientJoinedGame);
    cs->show();
    this->close();
}


void CreateGame::on_btnBack_clicked() {
    this->msg.setGameName("");
    this->msg.setMaxPlayers(0);
    this->msg.setWaitTime(0);

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }
    this->close();
}
