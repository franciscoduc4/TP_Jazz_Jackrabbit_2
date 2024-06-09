#include "sceneselection.h"

#include "../Common/Config/ClientConfig.h"
#include "../Common/Types/episode.h"

#include "creategame.h"
#include "ui_sceneselection.h"

SceneSelection::SceneSelection(QWidget* parent, LobbyController& controller, LobbyMessage& msg,
                               bool& clientJoinedGame):
        QDialog(parent),
        ui(new Ui::SceneSelection),
        controller(controller),
        msg(msg),
        clientJoinedGame(clientJoinedGame),
        sceneSpritesWidget(new SceneSpritesWidget(nullptr, ClientConfig::getEpisodesColourKey())) {
    ui->setupUi(this);
    QVBoxLayout* layout = new QVBoxLayout(ui->widgetScenes);
    layout->addWidget(sceneSpritesWidget);
}

SceneSelection::~SceneSelection() { delete ui; }

void SceneSelection::on_btnChoose_clicked() {
    size_t selection = sceneSpritesWidget->getCurrentSpriteIndex();
    Episode episode = static_cast<Episode>(selection + 1);
    this->msg.setEpisode(episode);
    CreateGame cg(this, this->controller, this->msg, this->clientJoinedGame);
    cg.show();
    this->close();
}


void SceneSelection::on_btnBack_clicked() {
    this->msg.setEpisode(Episode::INVALID);

    this->hide();

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }

    this->close();
}
