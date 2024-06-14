#include "mapselection.h"

#include "../Common/Config/ClientConfig.h"

#include "creategame.h"
#include "ui_mapselection.h"

MapSelection::MapSelection(QWidget* parent, LobbyController& controller, LobbyMessage& msg,
                               bool& clientJoinedGame):
        QDialog(parent),
        ui(new Ui::MapSelection),
        controller(controller),
        msg(msg),
        clientJoinedGame(clientJoinedGame),
        sceneSpritesWidget(new SceneSpritesWidget(nullptr, ClientConfig::getEpisodesColourKey())) {
    ui->setupUi(this);
    QVBoxLayout* layout = new QVBoxLayout(ui->widgetScenes);
    layout->addWidget(sceneSpritesWidget);
    sceneSpritesWidget->show();

    QFile file(":/Lobby/Styles/sceneselection.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
}

MapSelection::~MapSelection() {
    delete sceneSpritesWidget;
    delete ui;
}

void MapSelection::on_btnChoose_clicked() {
    // size_t selection = sceneSpritesWidget->getCurrentSpriteIndex();
    // Episode episode = static_cast<Episode>(selection + 1);
    // this->msg.setMap(episode);
    this->hide();
    auto cg = new CreateGame(this, this->controller, this->msg, this->clientJoinedGame);
    cg->show();
}


void MapSelection::on_btnBack_clicked() {
    // this->msg.setMap(Episode::INVALID);

    this->hide();

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }

    this->deleteLater();
}
