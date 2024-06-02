#include "sceneselection.h"
#include "ui_sceneselection.h"

#include "../Common/Constants/episodeSelect.h"
#include "creategame.h"

SceneSelection::SceneSelection(QWidget *parent, QTMonitor& monitor, LobbyMessage& msg) :
    QMainWindow(parent),
    ui(new Ui::SceneSelection),
    monitor(monitor),
    msg(msg),
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
    size_t selection = sceneSpritesWidget->getCurrentSpriteIndex();
    EpisodeSelect episode = static_cast<EpisodeSelect>(selection + 1);
    this->msg.setEpisode(episode);
    CreateGame* cg = new CreateGame(this, this->monitor, this->msg);
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

