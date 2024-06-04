#include "sceneselection.h"
#include "ui_sceneselection.h"

#include "../Common/Constants/episodeSelect.h"
#include "creategame.h"

SceneSelection::SceneSelection(QWidget *parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame) :
    QMainWindow(parent),
    ui(new Ui::SceneSelection),
    client(client),
    msg(msg),
    clientJoinedGame(clientJoinedGame)
    sceneSpritesWidget(new SceneSpritesWidget)
{
    ui->setupUi(this);
    QVBoxLayout* layout = new QVBoxLayout(ui->widgetScenes);
    layout->addWidget(sceneSpritesWidget);
}

SceneSelection::~SceneSelection()
{
    delete ui;
}

void SceneSelection::on_btnChoose_clicked()
{
    size_t selection = sceneSpritesWidget->getCurrentSprite();
    EpisodeSelect episode = static_cast<EpisodeSelect>(selection + 1);
    this->msg.setEpisode(episode);
    CreateGame* cg = new CreateGame(this, this->client, this->msg, this->clientJoinedGame);
    cg->show();
    this->close();
}


void SceneSelection::on_btnBack_clicked()
{
    this->msg.setEpisode(EpisodeSelect::INVALID);
    QWidget* parent = this->parentWidget();
    if (parent){
        parent->show();
    }
    this->close();
}

