#include "waitingroom.h"

#include <QFile>

#include "ui_waitingroom.h"

WaitingRoom::WaitingRoom(QWidget *parent, LobbyController& controller, LobbyMessage& msg, bool& clientJoinedGame) :
    QDialog (parent),
    ui(new Ui::WaitingRoom),
    controller(controller),
    msg(msg),
    clientJoinedGame(clientJoinedGame)
{
    ui->setupUi(this);

    QString gameName = QString::fromStdString(this->msg.getGameName());
    ui->labelGameName->setText(gameName);

    if (this->msg.getLobbyCmd() == Command::CREATE_GAME) {
        QString maxPlayers = QString::number(this->msg.getMaxPlayers());
        ui->maxPlayers->setText(maxPlayers);
    }

    QFile file(":/Lobby/Styles/waitingroom.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelGameName->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelPlayers->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelSlash->setAttribute(Qt::WA_TranslucentBackground);
    ui->numPlayers->setAttribute(Qt::WA_TranslucentBackground);
    ui->maxPlayers->setAttribute(Qt::WA_TranslucentBackground);
}

WaitingRoom::~WaitingRoom()
{
    delete ui;
}

