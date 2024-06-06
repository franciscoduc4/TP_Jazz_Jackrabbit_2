#include "lobby.h"

#include "../Common/Constants/lobbyCommands.h"

#include "characterselection.h"
#include "sceneselection.h"
#include "ui_lobby.h"

Lobby::Lobby(QWidget* parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame):
        QDialog(parent),
        ui(new Ui::Lobby),
        client(client),
        msg(msg),
        clientJoinedGame(clientJoinedGame) {
    ui->setupUi(this);
    QString playerName = QString::fromStdString(this->msg.getPlayerName());
    QString welcomeText = ui->labelTitle->text();
    welcomeText.append(playerName);
    ui->labelTitle->setText(welcomeText);
}

Lobby::~Lobby() { delete ui; }

void Lobby::on_btnCreateGame_clicked() {
    // this->msg.setLobbyCmd(LobbyCommands::CREATE_GAME);

    this->hide();

    SceneSelection ss(this, this->client, this->msg, this->clientJoinedGame);
    ss.setModal(true);
    ss.exec();

    this->close();
}


void Lobby::on_btnJoinGame_clicked() {
    // this->msg.setLobbyCmd(LobbyCommands::JOIN_GAME);

    this->hide();

    CharacterSelection cs(this, this->client, this->msg, this->clientJoinedGame);
    cs.setModal(true);
    cs.exec();

    this->close();
}


void Lobby::on_btnBack_clicked() {
    // this->msg.setLobbyCmd(LobbyCommands::INVALID_CMD);
    this->hide();

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }

    this->close();
}
