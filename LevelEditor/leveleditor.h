#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCore>
#include <QPixmap>
#include <unordered_map>

#include <yaml-cpp/yaml.h>

#include "SpritesManager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class LevelEditor;
}
QT_END_NAMESPACE

class LevelEditor : public QMainWindow {
    Q_OBJECT

public:
    explicit LevelEditor(QWidget* parent = nullptr);
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;
    ~LevelEditor();

private slots:
    void onSaveClicked();

private:
    Ui::LevelEditor *ui;
    QPixmap mapCanvas;
    std::unordered_map<QString, std::vector<QPoint>> elementData;

    enum class ElementCategory {
        OBSTACLE,
        ENEMY,
        GEM,
        GOLD_COIN,
        SILVER_COIN,
        FOOD,
        PLAYER
    };

    std::unordered_map<QString, ElementCategory> elementCategories = {
            {"FULL_FLOOR", ElementCategory::OBSTACLE},
            {"LARGE_WOOD_FLOOR", ElementCategory::OBSTACLE},
            {"LEFT_LADDER", ElementCategory::OBSTACLE},
            {"LONG_PLATFORM", ElementCategory::OBSTACLE},
            {"RIGHT_LADDER", ElementCategory::OBSTACLE},
            {"SMALL_PLATFORM", ElementCategory::OBSTACLE},
            {"WOOD_FLOOR", ElementCategory::OBSTACLE},
            {"WOOD_LARGE_COLUMN", ElementCategory::OBSTACLE},
            {"TURTLE", ElementCategory::ENEMY},
            {"SCHWARZENGUARD", ElementCategory::ENEMY},
            {"YELLOWMON", ElementCategory::ENEMY},
            {"GEM", ElementCategory::GEM},
            {"GOLD_COIN", ElementCategory::GOLD_COIN},
            {"SILVER_COIN", ElementCategory::SILVER_COIN},
            {"FOOD", ElementCategory::FOOD},
            {"JAZZ", ElementCategory::PLAYER},
            {"SPAZ", ElementCategory::PLAYER},
            {"LORI", ElementCategory::PLAYER}
    };
};

#endif // LEVELEDITOR_H
