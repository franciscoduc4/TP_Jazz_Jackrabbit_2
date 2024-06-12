#include "sceneselection.h"

#include "../Common/Config/ClientConfig.h"

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
    sceneSpritesWidget->show();

    QFile file(":/Lobby/Styles/sceneselection.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
}

SceneSelection::~SceneSelection() {
    delete sceneSpritesWidget;
    delete ui;
}

void SceneSelection::on_btnChoose_clicked() {
    // size_t selection = sceneSpritesWidget->getCurrentSpriteIndex();
    // Episode episode = static_cast<Episode>(selection + 1);
    // this->msg.setEpisode(episode);
    this->hide();
    CreateGame cg(this, this->controller, this->msg, this->clientJoinedGame);
    cg.setModal(true);
    cg.exec();
    this->close();
}


void SceneSelection::on_btnBack_clicked() {
    this->msg.setEpisode(" ");

    this->hide();

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }

    this->close();
}
