#include "leveleditor.h"

#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <iostream>

#include "canvaswidget.h"
#include "droppedElement.h"
#include "ui_leveleditor.h"

LevelEditor::LevelEditor(QWidget* parent)
        : QMainWindow(parent), ui(new Ui::LevelEditor) {
    ui->setupUi(this);

    // Populate the QTreeWidget
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

    // Replace the gridLayoutWidget with an instance of CanvasWidget
    auto *canvasWidget = new CanvasWidget(this);
    ui->gridLayout->addWidget(canvasWidget);
    ui->gridLayoutWidget->setStyleSheet("border: 1px solid white;");

    // Connect the dropped signal from CanvasWidget to a slot in LevelEditor
    connect(canvasWidget, &CanvasWidget::dropped, this, &LevelEditor::handleDropEvent);
    connect(ui->elementsTree, &QTreeWidget::itemSelectionChanged, this, &LevelEditor::onSelectionChanged);
    qDebug() << "Level Editor Created";
}

LevelEditor::~LevelEditor() {
    delete ui;
}

void LevelEditor::onSelectionChanged() {
    QList<QTreeWidgetItem*> selectedItems = ui->elementsTree->selectedItems();
    for (const auto& item : selectedItems) {
        qDebug() << "Selected item: " << item->text(0);

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);

        QString elementType = item->text(0);
        QString elementName = elementNames[elementType];
        QPixmap sprite = SpritesManager::get(elementName); // Set this to the desired sprite

        dataStream << elementType << sprite;

        auto *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);

        auto *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(sprite);
        // drag->setHotSpot(QPoint(sprite.width()/2, sprite.height()/2));

        drag->exec(Qt::CopyAction | Qt::MoveAction);
    }
}

void LevelEditor::handleDropEvent(QDropEvent* event) {
    qDebug() << "Handle Drop Event called";
    QByteArray encoded = event->mimeData()->data("application/x-dnditemdata");
    QDataStream stream(&encoded, QIODevice::ReadOnly);
    qDebug() << "Handle Drop Event";
    while (!stream.atEnd()) {
        QString elementType;
        QPixmap sprite;

        stream >> elementType >> sprite;

        // Get drop position and convert to game map coordinates
        QPoint dropPos = event->pos();

        qDebug() << "Drop Pos: " << dropPos.x() << " " << dropPos.y();

        int mapX = static_cast<int>(dropPos.x());
        int mapY = static_cast<int>(dropPos.y());

        qDebug() << "Map X: " << mapX << " Map Y: " << mapY;

        // Store element position for saving
        elementData[elementType].emplace_back(mapX, mapY);
        qDebug() << "Element Data Size: " << elementData.size();
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
        QMessageBox(QMessageBox::Warning, "Error", "El mapa no puede estar vacÃ­o").exec();
        return;
    }

    QString mapName = "../src/maps/" + ui->mapName->text().trimmed() + ".yaml";
    QFile file(mapName);
    if (file.exists()) {
        QMessageBox(QMessageBox::Warning, "Error", "A map with this name already exists").exec();
        return;
    }

    for (const auto& pair: elementData) {
        qDebug() << pair.first << " : " << pair.second.size();
        QString elementName = elementNames[pair.first];
        ElementCategory category = elementCategories[elementName];
        qDebug() << "Category: " << static_cast<int>(category);
        qDebug() << "Element Name: " << elementName;
        elementPositions[category][elementName] = pair.second;
        qDebug() << "Element positions [category][elementName] size: " << elementPositions[category][elementName].size();
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
        qDebug() << "Category: " << categoryNames[category.first];
        for (const auto& element : category.second) {
            out << YAML::Key << element.first.toStdString();
            out << YAML::Value << YAML::BeginSeq;
            qDebug() << "Element: " << element.first;
            for (const auto& point : element.second) {
                qDebug() << "Point: " << point.x() << " " << point.y();
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
}

void LevelEditor::closeEvent(QCloseEvent* event) {
    SpritesManager::deleteInstance();
    event->accept();
}
