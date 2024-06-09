#include "creategame.h"

#include <QMessageBox>

#include "characterselection.h"
#include "ui_creategame.h"

CreateGame::CreateGame(QWidget* parent, LobbyController& controller, LobbyMessage& msg, bool& clientJoinedGame):
        QDialog(parent),
        ui(new Ui::CreateGame),
        controller(controller),
        msg(msg),
        clientJoinedGame(clientJoinedGame) {
    ui->setupUi(this);
}

CreateGame::~CreateGame() { delete ui; }

void CreateGame::on_btnCreate_clicked() {

    QString gameName = ui->gameName->text();
    int numPlayers = ui->numPlayers->value();

    if (gameName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese un nombre para la partida");
        return;
    }
    this->msg.setGameName(gameName.toStdString());
    this->msg.setMaxPlayers(numPlayers);

    this->hide();

    CharacterSelection cs(this, this->controller, this->msg, this->clientJoinedGame);
    cs.setModal(true);
    cs.exec();
    this->close();
}


void CreateGame::on_btnBack_clicked() {
    this->msg.setGameName("");
    this->msg.setMaxPlayers(0);

    this->hide();

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }

    this->close();
}
