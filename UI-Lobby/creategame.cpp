#include "creategame.h"
#include "ui_creategame.h"

#include "characterselection.h"

CreateGame::CreateGame(QWidget *parent, QTMonitor& monitor, LobbyMessage& msg) :
    QMainWindow(parent),
    ui(new Ui::CreateGame),
    monitor(monitor),
    msg(msg)
{
    ui->setupUi(this);
}

CreateGame::~CreateGame()
{
    delete ui;
}

void CreateGame::on_btnCreate_clicked()
{
    QString gameName = ui->gameName->text();
    int numPlayers = ui->numPlayers->value();
    int waitTime = ui->waitTime->value();

    if (gameName.isEmpty()) {
        QMessageBox::warning(this, "Ingrese un nombre para la partida", "Warning");
        return;
    }
    this->msg.setGameName(gameName.toStdString());
    this->msg.setMaxPlayers(numPlayers);
    this->msg.setWaitTime(waitTime);

    CharacterSelection* cs = new CharacterSelection(this, this->monitor, this->msg);
    cs->show();
    this->close();
}


void CreateGame::on_btnBack_clicked()
{
    this->msg.setGameName("");
    this->msg.setMaxPlayers(0);
    this->msg.setWaitTime(0);

    QWidget* parent = this->parentWidget();
    if (parent){
        parent->show();
    }
    this->close();
}

