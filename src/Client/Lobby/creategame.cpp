#include "creategame.h"

#include <QMessageBox>

#include "characterselection.h"
#include "ui_creategame.h"

CreateGame::CreateGame(QWidget* parent, LobbyController& controller, LobbyMessage& msg,
                       bool& clientJoinedGame):
        QDialog(parent),
        ui(new Ui::CreateGame),
        controller(controller),
        msg(msg),
        clientJoinedGame(clientJoinedGame) {
    ui->setupUi(this);

    QFile file(":/Lobby/Styles/creategame.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelName->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelNumPlayers->setAttribute(Qt::WA_TranslucentBackground);
}

CreateGame::~CreateGame() {
    delete ui;
}

void CreateGame::on_btnCreate_clicked() {
    QString gameName = ui->gameName->text().trimmed();
    int numPlayers = ui->numPlayers->value();

    if (gameName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese un nombre para la partida");
        return;
    }

    this->msg.setLobbyCmd(Command::CREATE_GAME);
    this->msg.setGameName(gameName.toStdString());
    this->msg.setMaxPlayers(numPlayers);

    this->hide();

    auto cs = new CharacterSelection(this, this->controller, this->msg, this->clientJoinedGame);
    cs->show();
}

void CreateGame::on_btnBack_clicked() {
    this->msg.setGameName("");
    this->msg.setMaxPlayers(0);

    this->hide();

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }

    this->deleteLater();
}
