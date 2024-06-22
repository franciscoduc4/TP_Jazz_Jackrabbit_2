#include "leveleditor.h"

#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <iostream>

#include "droppedElement.h"
#include "dropwidget.h"
#include "ui_leveleditor.h"

LevelEditor::LevelEditor(QWidget* parent)
        : QMainWindow(parent), ui(new Ui::LevelEditor) {
    ui->setupUi(this);

    // Populate the QTreeWidget
    QStringList elements = {"Jazz", "Spaz", "Lori", "Food", "Gem", "Silver Coin", "Gold Coin", "Turtle", "Schwartzenguard", "Yellowmon", "Full Floor", "Large Wood Floor", "Left Ladder", "Long Platform", "Right Ladder", "Small Platform", "Wood Floor", "Wood Large Column"};
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

        // Calculate cell size based on grid layout dimensions
        int cellWidth = ui->gridLayoutWidget->width() / ui->gridLayout->columnCount();
        int cellHeight = ui->gridLayoutWidget->height() / ui->gridLayout->rowCount();

        // Get drop position and convert to game map coordinates
        QPoint dropPos = event->pos();
        int mapX = dropPos.x() * 1000 / cellWidth;
        int mapY = dropPos.y() * 1000 / cellHeight;

        // Store element position for saving
        elementData[elementType].emplace_back(mapX, mapY);

        QString elementName = elementNames[elementType];

        // Create a DroppedElement widget (assuming you have it)
        auto* elementWidget = new DroppedElement(elementType, SpritesManager::get(elementName));
        elementWidget->setFixedSize(cellWidth, cellHeight); // Set size based on cell size

        // Add the DroppedElement widget to the grid
        ui->gridLayout->addWidget(elementWidget, row, col);
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