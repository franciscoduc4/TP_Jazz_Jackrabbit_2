#include "sceneselection.h"
#include "ui_sceneselection.h"

#include "../Common/Constants/episodeSelect.h"

SceneSelection::SceneSelection(QWidget *parent, SenderThread& sender, ReceiverThread& receiver, QTMonitor& monitor, LobbyMessage& msg) :
    QMainWindow(parent),
    ui(new Ui::SceneSelection),
    sender(sender),
    receiver(receiver),
    monitor(monitor),
    msg(msg)
{
    ui->setupUi(this);
}

SceneSelection::~SceneSelection()
{
    delete ui;
}

void SceneSelection::on_btnChoose_clicked()
{
    // this->msg.setEpisode(EpisodeSelect::);
    CreateGame* cg = new CreateGame(this->sender, this->receiver, this->monitor, this->msg);
    cg->show();
    this->close();
}


void SceneSelection::on_btnBack_clicked()
{
    this->msg.setEpisode(EpisodeSelect::INVALID);
    Lobby* lobby = new Lobby(this->sender, this->receiver, this->monitor, this->msg);
    lobby->show();
    this->close();
}

