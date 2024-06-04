#include "lobby.h"
#include "ui_lobby.h"

#include "../Common/Constants/lobbyCommands.h"
#include "characterselection.h"

Lobby::Lobby(QWidget *parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame) :
    QMainWindow(parent),
    ui(new Ui::Lobby),
    client(client),
    msg(msg),
    clientJoinedGame(clientJoinedGame)
{
    ui->setupUi(this);
    QString playerName = QString::fromStdString(this->msg.getPlayerName());
    QString welcomeText = ui->labelTitle->text();
    welcomeText.append(playerName);
    ui->labelTitle->setText(welcomeText);
}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::on_btnCreateGame_clicked()
{
    this->msg.setLobbyCmd(LobbyCommands::CREATE_GAME);
    SceneSelection* ss = new SceneSelection(this, this->client, this->msg, this->clientJoinedGame);
    ss->show();
    this->close();
}


void Lobby::on_btnJoinGame_clicked()
{
    this->msg.setLobbyCmd(LobbyCommands::JOIN_GAME);
    CharacterSelection* cs = new CharacterSelection(this, this->client, this->msg, this->clientJoinedGame);
    cs->show();
    this->close();
}


void Lobby::on_btnBack_clicked()
{
    this->msg.setLobbyCmd(LobbyCommands::INVALID_CMD);
    QWidget* parent = this->parentWidget();
    if (parent){
        parent->show();
    }
    this->close();
}

