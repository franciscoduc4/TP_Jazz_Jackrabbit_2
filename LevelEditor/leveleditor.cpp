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
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->elementsTree);
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
        int gameMapX = dropPos.x() * 255 / ui->gridLayoutWidget->width();
        int gameMapY = dropPos.y() * 255 / ui->gridLayoutWidget->height();

        // Store the element position
        elementData[elementType].push_back(QPoint(gameMapX, gameMapY));
    }

    event->acceptProposedAction();
}

void LevelEditor::onSaveClicked() {
    YAML::Emitter out;
    out << YAML::BeginMap;

    for (const auto& pair : elementData) {
        out << YAML::Key << pair.first.toStdString();
        out << YAML::Value << YAML::BeginSeq;

        for (const auto& point : pair.second) {
            out << YAML::Flow << YAML::BeginSeq << point.x() << point.y() << YAML::EndSeq;
        }

        out << YAML::EndSeq;
    }

    out << YAML::EndMap;

    QString mapName = ui->mapName->text().trimmed() + ".yaml";
    // Save the YAML string to a file
    QFile file(mapName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << out.c_str();
        file.close();
    }
}