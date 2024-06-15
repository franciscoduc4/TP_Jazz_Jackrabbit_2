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
        buttonGroup(new QButtonGroup(this)) {
    ui->setupUi(this);

    this->controller.sendRequest(this->msg);

    std::unordered_map<uint32_t, std::string> maps = this->controller.getMaps();

    if (maps.empty()) {
        auto* msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("No hay mapas disponibles.");
        connect(msgBox, &QMessageBox::finished, this, &QDialog::show);
        msgBox->show();
        return;
    }

    // Iterate over the map data
    for (const auto& map : maps) {
        // Create a new QRadioButton with the map name as the label
        auto* radioButton = new QRadioButton(QString::fromStdString(map.second));

        buttonGroup->addButton(radioButton, map.first);

        ui->widgetScenes->layout()->addWidget(radioButton);
    }

    // Set a blurred background for the QWidget
    auto* blurEffect = new QGraphicsBlurEffect(this);
    ui->widgetScenes->setGraphicsEffect(blurEffect);

    QFile file(":/Lobby/Styles/sceneselection.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
}

MapSelection::~MapSelection()
{
    delete ui;
}

void MapSelection::on_btnChoose_clicked()
{
    if (buttonGroup->checkedId() == -1) {
        QMessageBox::information(this, "Error", "Seleccione un mapa para continuar.");
    } else {
        this->msg.setMap(buttonGroup->checkedId());
        this->hide();
        auto cg = new CreateGame(this, this->controller, this->msg, this->clientJoinedGame);
        cg->show();
    }
}

void MapSelection::on_btnBack_clicked()
{
    this->msg.setMap(-1);
    this->hide();

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }

    this->deleteLater();
}