#include "lobby.h"
#include "./ui_lobby.h"

Lobby::Lobby(QWidget *parent, Socket& skt)
    : QMainWindow(parent)
    , ui(new Ui::Lobby)
    , skt(skt)
{
    ui->setupUi(this);
}

Lobby::~Lobby()
{
    delete ui;
}


void Lobby::on_btnIngresar_clicked()
{
    QString playerName = ui->inputName->text();

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ingrese su nombre para ingresar.");
        return;
    }

    Lobby *lobby = new Lobby(playerName, this->skt);
    lobby->show();
    this->close();
}

