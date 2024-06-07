#include "welcome.h"

#include <QFile>
#include <QKeyEvent>

#include "lobby.h"
#include "ui_welcome.h"

Welcome::Welcome(QWidget* parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame):
        QMainWindow(parent),
        ui(new Ui::Welcome),
        client(client),
        msg(msg),
        clientJoinedGame(clientJoinedGame) {
    ui->setupUi(this);
    QFile file(":/Lobby/Styles/welcome.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelName->setAttribute(Qt::WA_TranslucentBackground);
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

void Welcome::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        on_btnIngresar_clicked();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}