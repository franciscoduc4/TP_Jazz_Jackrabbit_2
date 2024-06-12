#include "lobby.h"

#include "characterselection.h"
#include "mapselection.h"
#include "ui_lobby.h"

Lobby::Lobby(QWidget* parent, LobbyController& controller, LobbyMessage& msg, bool& clientJoinedGame):
        QDialog(parent),
        ui(new Ui::Lobby),
        controller(controller),
        msg(msg),
        clientJoinedGame(clientJoinedGame) {
    ui->setupUi(this);

    QString playerName = QString::fromStdString(this->msg.getPlayerName());
    QString welcomeText = ui->labelTitle->text();
    welcomeText.append(playerName);
    ui->labelTitle->setText(welcomeText);

    QFile file(":/Lobby/Styles/lobby.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    ui->centralwidget->setStyleSheet(styleSheet);

    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
}

Lobby::~Lobby() { delete ui; }

void Lobby::on_btnCreateGame_clicked() {
    this->msg.setLobbyCmd(Command::CREATE_GAME);

    this->hide();

    auto ms = new MapSelection(this, this->controller, this->msg, this->clientJoinedGame);
    ms->show();

}


void Lobby::on_btnJoinGame_clicked() {
    this->msg.setLobbyCmd(Command::JOIN_GAME);

    this->hide();

    auto cs = new CharacterSelection(this, this->controller, this->msg, this->clientJoinedGame);
    cs->show();

}


void Lobby::on_btnBack_clicked() {
    this->msg.setLobbyCmd(Command::IDLE);
    this->hide();

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }

    this->deleteLater();
}
