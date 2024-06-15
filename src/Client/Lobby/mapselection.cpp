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
    std::cout << "[MAP SELECTION] UI setup completed" << std::endl;

    this->controller.sendRequest(this->msg);
    std::cout << "[MAP SELECTION] Request sent to controller" << std::endl;

    std::unordered_map<uint8_t, std::string> maps = this->controller.getMaps();
    std::cout << "[MAP SELECTION] Maps received: " << maps.size() << std::endl;

    if (maps.empty()) {
        std::cout << "[MAP SELECTION] No maps available" << std::endl;
        auto* msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("No hay mapas disponibles.");
        connect(msgBox, &QMessageBox::finished, this, &QDialog::show);
        msgBox->show();
        return;
    }

    std::cout << "[MAP SELECTION] Populating map selection UI" << std::endl;

    // Check if ui->widgetScenes has a layout, if not create one
    if (!ui->widgetScenes->layout()) {
        std::cout << "[MAP SELECTION] ui->widgetScenes has no layout, creating one" << std::endl;
        ui->widgetScenes->setLayout(new QVBoxLayout());
    }

    // Iterate over the map data
    for (const auto& [id, name]: maps) {
        auto* radioButton = new QRadioButton(QString::fromStdString(name));
        buttonGroup->addButton(radioButton, id);
        ui->widgetScenes->layout()->addWidget(radioButton);
        std::cout << "[MAP SELECTION] Added map: " << name << " with ID: " << static_cast<int>(id)
                  << std::endl;
    }
}

MapSelection::~MapSelection() {
    delete ui;
    std::cout << "[MAP SELECTION] Destructor called, UI deleted" << std::endl;
}

void MapSelection::on_btnChoose_clicked() {
    std::cout << "[MAP SELECTION] Choose button clicked" << std::endl;
    if (buttonGroup->checkedId() == -1) {
        QMessageBox::information(this, "Error", "Seleccione un mapa para continuar.");
        std::cout << "[MAP SELECTION] No map selected, showing error message" << std::endl;
    } else {
        this->msg.setMap(buttonGroup->checkedId());
        std::cout << "[MAP SELECTION] Map selected with ID: " << buttonGroup->checkedId()
                  << std::endl;
        this->hide();
        auto cg = new CreateGame(this, this->controller, this->msg, this->clientJoinedGame);
        cg->show();
        std::cout << "[MAP SELECTION] CreateGame dialog shown" << std::endl;
    }
}

void MapSelection::on_btnBack_clicked() {
    std::cout << "[MAP SELECTION] Back button clicked" << std::endl;
    this->msg.setMap(-1);
    this->hide();
    std::cout << "[MAP SELECTION] Map deselected and dialog hidden" << std::endl;

    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
        std::cout << "[MAP SELECTION] Parent widget shown" << std::endl;
    }

    this->deleteLater();
    std::cout << "[MAP SELECTION] Dialog marked for deletion" << std::endl;
}
