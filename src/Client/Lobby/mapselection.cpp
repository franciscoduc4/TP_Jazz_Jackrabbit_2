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

    std::unordered_map<uint8_t, std::string> maps = this->controller.getMaps();

    if (maps.empty()) {
        auto* msgBox = new QMessageBox(this);
        msgBox->setIcon(QMessageBox::Information);
        msgBox->setText("No hay mapas disponibles.");
        connect(msgBox, &QMessageBox::finished, this, &QDialog::show);
        msgBox->show();
        return;
    }

    if (!ui->widgetScenes->layout()) {
        ui->widgetScenes->setLayout(new QVBoxLayout());
    }

    for (const auto& [id, name]: maps) {
        QString mapName = QString::fromStdString(name);

        if (mapName.endsWith(".yaml")) {
            mapName.remove(".yaml");
        } else if (mapName.endsWith(".yml")) {
            mapName.remove(".yml");
        }

        auto* button = new QPushButton(mapName);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        button->setCheckable(true);

        QFont font("Jazz Jackrabbit 2");
        font.setPointSize(30);
        QFontMetrics fm(font);
        int textWidth = fm.horizontalAdvance(button->text());

        while (textWidth > button->width() && font.pointSize() > 1) {
            font.setPointSize(font.pointSize() - 1);
            fm = QFontMetrics(font);
            textWidth = fm.horizontalAdvance(button->text());
        }

        button->setFont(font);

        buttonGroup->addButton(button, id);
        ui->widgetScenes->layout()->addWidget(button);
    }

    QFile file(":/Lobby/Styles/mapselection.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelTitle->setAttribute(Qt::WA_TranslucentBackground);
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