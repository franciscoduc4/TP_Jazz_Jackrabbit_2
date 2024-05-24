#include "welcome.h"
#include "./ui_welcome.h"

Welcome::Welcome(QWidget *parent, SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg)
    : QMainWindow(parent),
      ui(new Ui::Welcome),
      sender(sender),
      receiver(receiver),
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

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ingrese su nombre para ingresar.");
        return;
    }

    this->msg.setPlayerName(playerName.toStdString());

    Lobby* lobby = new Lobby(this->sender, this->receiver, this->monitor, this->msg);
    lobby->show();
    this->close();
}

