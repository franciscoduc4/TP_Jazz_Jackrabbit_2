#include "creategame.h"
#include "ui_creategame.h"

CreateGame::CreateGame(QWidget *parent, SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg) :
    QMainWindow(parent),
    ui(new Ui::CreateGame),
    sender(sender),
    receiver(receiver),
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
        QMessageBox::warning(this, "Ingrese un nombre para la partida");
        return;
    }
    this->msg.setGameName(gameName.toStdString());
    this->msg.setMaxPlayers(numPlayers);
    this->msg.setWaitTime(waitTime);

    CharacterSelection* cs = new CharacterSelection(this->sender, this->receiver, this->monitor, this->msg);
    cs->show();
    this->close();
}


void CreateGame::on_btnBack_clicked()
{
    this->msg.setGameName("");
    this->msg.setMaxPlayers(0);
    this->msg.setWaitTime(0);

    SceneSelection* ss = new SceneSelection(this->sender, this->receiver, this->monitor, this->msg);
    ss->show();
    this->close();
}

