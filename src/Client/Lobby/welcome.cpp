#include "welcome.h"

#include <QFile>
#include <QKeyEvent>

#include "lobby.h"
#include "ui_welcome.h"

Welcome::Welcome(QWidget* parent, LobbyController& controller, LobbyMessage& msg, bool& clientJoinedGame):
        QMainWindow(parent),
        ui(new Ui::Welcome),
        controller(controller),
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
    QString playerName = ui->inputName->text().trimmed();

    if (playerName.isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese su nombre para ingresar.");
        return;
    }

    this->msg.setPlayerName(playerName.toStdString());

    auto lobby = new Lobby(this, this->controller, this->msg, this->clientJoinedGame);
    this->hide();
    lobby->show();
}

void Welcome::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        on_btnIngresar_clicked();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}