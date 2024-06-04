#include "welcome.h"
#include "ui_welcome.h"

#include "lobby.h"

Welcome::Welcome(QWidget *parent, QTMonitor& monitor, LobbyMessage& msg)
    : QMainWindow(parent),
      ui(new Ui::Welcome),
      monitor(monitor),
      msg(msg)
{
    ui->setupUi(this);
}

Welcome::~Welcome()
{
    delete ui;
}


void Welcome::on_btnIngresar_clicked()
{
    QString playerName = ui->inputName->text();

    if (playerName.isEmpty()) {
        QMessageBox::warning(this, "Ingrese su nombre para ingresar.", "Warning");
        return;
    }

    this->msg.setPlayerName(playerName.toStdString());

    Lobby* lobby = new Lobby(this, this->monitor, this->msg);
    lobby->show();
    this->close();
}

