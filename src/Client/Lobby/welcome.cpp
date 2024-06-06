#include "welcome.h"

#include "lobby.h"
#include "ui_welcome.h"

Welcome::Welcome(QWidget* parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame):
        QMainWindow(parent),
        ui(new Ui::Welcome),
        client(client),
        msg(msg),
        clientJoinedGame(clientJoinedGame) {
    ui->setupUi(this);
}

Welcome::~Welcome() { delete ui; }


void Welcome::on_btnIngresar_clicked() {
    QString playerName = ui->inputName->text();

    if (playerName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese su nombre para ingresar.");
        return;
    }

    this->msg.setPlayerName(playerName.toStdString());

    this->hide();

    Lobby lobby(this, this->client, this->msg, this->clientJoinedGame);
    lobby.setModal(true);
    lobby.exec();
}
