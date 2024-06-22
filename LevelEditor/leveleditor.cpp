#include "leveleditor.h"
#include "dropwidget.h"

#include "ui_leveleditor.h"

#include <QDrag>
#include <QMimeData>
#include <QPainter>

#include <iostream>

LevelEditor::LevelEditor(QWidget* parent)
        : QMainWindow(parent), ui(new Ui::LevelEditor) {
    ui->setupUi(this);

    // Populate the QTreeWidget
    QStringList elements = {"Jazz", "Spaz", "Lori", "Food", "Gems", "Silver Coins", "Gold Coins", "Turtle", "Schwartzenguard", "Yellowmon", "Full Floor", "Large Wood Floor", "Left Ladder", "Long Platform", "Right Ladder", "Small Platform", "Wood Floor", "Wood Large Column"};
    for (const auto& element : elements) {
        auto* item = new QTreeWidgetItem(ui->elementsTree);
        item->setText(0, element);
    }

    // Enable drag and drop for the QTreeWidget
    ui->elementsTree->setDragEnabled(true);
    ui->elementsTree->viewport()->setAcceptDrops(true);
    ui->elementsTree->setDropIndicatorShown(true);

    QFile file(":/Styles/editor.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    ui->centralwidget->setStyleSheet(styleSheet);
    ui->labelMapName->setAttribute(Qt::WA_TranslucentBackground);

    // Connect the save button click event
    connect(ui->btnSave, &QPushButton::clicked, this, &LevelEditor::onSaveClicked);

    // Replace the gridLayoutWidget with an instance of DropWidget
    auto *dropWidget = new DropWidget(this);
    ui->gridLayoutWidget->layout()->addWidget(dropWidget);
    ui->gridLayoutWidget->setStyleSheet("border: 1px solid white;");

    // Connect the dropped signal from DropWidget to a slot in LevelEditor
    connect(dropWidget, &DropWidget::dropped, this, &LevelEditor::handleDropEvent);
}

LevelEditor::~LevelEditor() {
    delete ui;
}

void LevelEditor::handleDropEvent(QDropEvent* event) {
    QByteArray encoded = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
    QDataStream stream(&encoded, QIODevice::ReadOnly);
    while (!stream.atEnd()) {
        int row, col;
        QMap<int, QVariant> roleDataMap;
        stream >> row >> col >> roleDataMap;

        QString elementType = roleDataMap[Qt::DisplayRole].toString();

        // Calculate the grid cell size
        int cellWidth = ui->gridLayoutWidget->width() / ui->gridLayout->columnCount();
        int cellHeight = ui->gridLayoutWidget->height() / ui->gridLayout->rowCount();

        // Get the drop position
        QPoint dropPos = event->pos();

        // Convert the drop position to the game map dimensions
        int gridX = dropPos.x() * ui->gridLayout->columnCount() / ui->gridLayoutWidget->width();
        int gridY = dropPos.y() * ui->gridLayout->rowCount() / ui->gridLayoutWidget->height();

        int mapX = gridX * 1000 / ui->gridLayout->columnCount();
        int mapY = gridY * 1000 / ui->gridLayout->rowCount();

        QString elementName = elementNames[elementType];
        // Store the element position
        elementData[elementName].emplace_back(mapX, mapY);

        // Create a QLabel and set its pixmap to the sprite
        auto* spriteLabel = new QLabel(this);
        spriteLabel->setPixmap(SpritesManager::get(elementType));

        // Set the QLabel's size to match the grid cell size
        spriteLabel->setFixedSize(cellWidth, cellHeight);

        // Add the QLabel to the grid at the dropped position
        ui->gridLayout->addWidget(spriteLabel, gridY, gridX);
    }

    event->acceptProposedAction();
}

void LevelEditor::onSaveClicked() {
    QString mapNameTrimmed = ui->mapName->text().trimmed();
    if (mapNameTrimmed.isEmpty()) {
        QMessageBox(QMessageBox::Warning, "Error", "El mapa necesita un nombre").exec();
        return;
    }

    if (elementData.empty()) {
        QMessageBox(QMessageBox::Warning, "Error", "El mapa no puede estar vacío").exec();
        return;
    }

    QString mapName = "../src/maps/" + ui->mapName->text().trimmed() + ".yaml";
    QFile file(mapName);
    if (file.exists()) {
        QMessageBox(QMessageBox::Warning, "Error", "A map with this name already exists").exec();
        return;
    }

    for (const auto& pair: elementData) {
        QString elementName = pair.first;
        ElementCategory category = elementCategories[elementName];
        elementPositions[category][elementName] = pair.second;
    }

    createYAML(mapName);

    QCoreApplication::exit(0);
}

void LevelEditor::createYAML(const QString& mapName) {
    YAML::Emitter out;
    out << YAML::BeginMap;

    // Add the size of the map
    out << YAML::Key << "SIZE";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "WIDTH" << YAML::Value << 1000;
    out << YAML::Key << "HEIGHT" << YAML::Value << 1000;
    out << YAML::EndMap;

    // Add the elements for each category
    for (const auto& category : elementPositions) {
        out << YAML::Key << categoryNames[category.first].toStdString();
        out << YAML::Value << YAML::BeginMap;
        for (const auto& element : category.second) {
            out << YAML::Key << element.first.toStdString();
            out << YAML::Value << YAML::BeginSeq;
            for (const auto& point : element.second) {
                out << YAML::Flow << YAML::BeginSeq << point.x() << point.y() << YAML::EndSeq;
            }
            out << YAML::EndSeq;
        }
        out << YAML::EndMap;
    }

    out << YAML::EndMap;

    // Save the YAML string to a file
    QFile file(mapName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << out.c_str();
        file.close();
    }
};

void LevelEditor::closeEvent(QCloseEvent* event) {
    SpritesManager::deleteInstance();
    event->accept();
}