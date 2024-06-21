#include "leveleditor.h"

#include "ui_leveleditor.h"

#include <QDrag>
#include <QMimeData>
#include <QPainter>

LevelEditor::LevelEditor(QWidget* parent)
        : QMainWindow(parent), ui(new Ui::LevelEditor) {
    ui->setupUi(this);

    // Populate the QTreeWidget
    QStringList elements = {"Jazz", "Spaz", "Lori", "Food", "Gems", "Silver Coins", "Gold Coins", "Respawn Point", "Turtle", "Schwartzenguard", "Yellowmon", "Full Floor", "Large Wood Floor", "Left Ladder", "Long Platform", "Right Ladder", "Small Platform", "Wood Floor", "Wood Large Column"};
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
}

LevelEditor::~LevelEditor() {
    delete ui;
}

void LevelEditor::dragEnterEvent(QDragEnterEvent* event) {
    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
        event->acceptProposedAction();
    }
}

void LevelEditor::dropEvent(QDropEvent* event) {
    QByteArray encoded = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
    QDataStream stream(&encoded, QIODevice::ReadOnly);
    while (!stream.atEnd()) {
        int row, col;
        QMap<int, QVariant> roleDataMap;
        stream >> row >> col >> roleDataMap;

        QString elementType = roleDataMap[Qt::DisplayRole].toString();

        // Get the drop position
        QPoint dropPos = event->pos();

        // Convert the drop position to the game map dimensions
        int gameMapX = dropPos.x() * 1000 / ui->gridLayoutWidget->width();
        int gameMapY = dropPos.y() * 1000 / ui->gridLayoutWidget->height();

        // Store the element position
        elementData[elementType].emplace_back(gameMapX, gameMapY);

        // Create a QLabel and set its pixmap to the sprite
        auto* spriteLabel = new QLabel(this);
        spriteLabel->setPixmap(SpritesManager::get(elementType.toUpper()));

        // Add the QLabel to the grid at the dropped position
        ui->gridLayout->addWidget(spriteLabel, gameMapY, gameMapX);
    }

    event->acceptProposedAction();
}

void LevelEditor::onSaveClicked() {
    QString mapNameTrimmed = ui->mapName->text().trimmed();
    if (mapNameTrimmed.isEmpty()) {
        QMessageBox(QMessageBox::Warning, "Error", "El mapa necesita un nombre").exec();
    }

    YAML::Emitter out;
    out << YAML::BeginMap;

    // Add the size of the map
    out << YAML::Key << "SIZE";
    out << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "WIDTH" << YAML::Value << 1000;
    out << YAML::Key << "HEIGHT" << YAML::Value << 1000;
    out << YAML::EndMap;

    // Categorize the elements
    std::unordered_map<ElementCategory, std::vector<QPoint>> categorizedData;
    for (const auto& pair : elementData) {
        ElementCategory category = elementCategories[pair.first];
        categorizedData[category].insert(categorizedData[category].end(), pair.second.begin(), pair.second.end());
    }

    // Add the elements for each category
    for (const auto& pair : categorizedData) {
        QString categoryName;
        switch (pair.first) {
            case ElementCategory::OBSTACLE:
                categoryName = "OBSTACLES";
                break;
            case ElementCategory::ENEMY:
                categoryName = "ENEMIES";
                break;
            case ElementCategory::GEM:
                categoryName = "GEMS";
                break;
            case ElementCategory::GOLD_COIN:
                categoryName = "GOLD_COINS";
                break;
            case ElementCategory::SILVER_COIN:
                categoryName = "SILVER_COINS";
                break;
            case ElementCategory::FOOD:
                categoryName = "FOOD";
                break;
            case ElementCategory::PLAYER:
                categoryName = "PLAYERS";
                break;
        }

        out << YAML::Key << categoryName.toStdString();
        out << YAML::Value << YAML::BeginSeq;

        for (const auto& point : pair.second) {
            out << YAML::Flow << YAML::BeginSeq << point.x() << point.y() << YAML::EndSeq;
        }

        out << YAML::EndSeq;
    }

    out << YAML::EndMap;

    QString mapName = "../src/maps/" + ui->mapName->text().trimmed() + ".yaml";
    // Save the YAML string to a file
    QFile file(mapName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << out.c_str();
        file.close();
    }
}