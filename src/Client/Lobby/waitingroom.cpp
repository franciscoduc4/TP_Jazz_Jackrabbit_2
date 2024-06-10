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

    QFile file(":/Lobby/Styles/waitingroom.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelPlayers->setAttribute(Qt::WA_TranslucentBackground);
    ui->labelSlash->setAttribute(Qt::WA_TranslucentBackground);
}

WaitingRoom::~WaitingRoom()
{
    delete ui;
}

void WaitingRoom::on_btnBack_clicked() {
     this->hide();

     QWidget* parent = this->parentWidget();
     if (parent) {
         parent->show();
     }

     this->close();
}

