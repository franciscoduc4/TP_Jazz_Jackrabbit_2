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
    void handleDropEvent(QDropEvent* event);
    void closeEvent(QCloseEvent* event) override;
    ~LevelEditor();

private slots:
    void onSaveClicked();

private:
    Ui::LevelEditor *ui;
    QPixmap mapCanvas;
    std::unordered_map<QString, std::vector<QPoint>> elementData;

    std::unordered_map<QString, QString> elementNames = {
            {"Full Floor", "FULL_FLOOR"},
            {"Large Wood Floor", "LARGE_WOOD_FLOOR"},
            {"Left Ladder", "LEFT_LADDER"},
            {"Long Platform", "LONG_PLATFORM"},
            {"Right Ladder", "RIGHT_LADDER"},
            {"Small Platform", "SMALL_PLATFORM"},
            {"Wood Floor", "WOOD_FLOOR"},
            {"Wood Large Column", "WOOD_LARGE_COLUMN"},
            {"Turtle", "TURTLES"},
            {"Schwartzenguard", "SCHWARZENGUARDS"},
            {"Yellowmon", "YELLOWMONS"},
            {"Gem", "GEMS"},
            {"Gold Coin", "GOLD_COINS"},
            {"Silver Coin", "SILVER_COINS"},
            {"Food", "FOOD"},
            {"Jazz", "JAZZ"},
            {"Spaz", "SPAZ"},
            {"Lori", "LORI"}
    };

    enum class ElementCategory {
        OBSTACLE,
        ENEMY,
        ITEM,
        PLAYER
    };

    std::unordered_map<ElementCategory, QString> categoryNames = {
            {ElementCategory::OBSTACLE, "OBSTACLES"},
            {ElementCategory::ENEMY, "ENEMIES"},
            {ElementCategory::ITEM, "ITEMS"},
            {ElementCategory::PLAYER, "PLAYERS"}
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
            {"GEM", ElementCategory::ITEM},
            {"GOLD_COIN", ElementCategory::ITEM},
            {"SILVER_COIN", ElementCategory::ITEM},
            {"FOOD", ElementCategory::ITEM},
            {"JAZZ", ElementCategory::PLAYER},
            {"SPAZ", ElementCategory::PLAYER},
            {"LORI", ElementCategory::PLAYER}
    };

    std::unordered_map<ElementCategory, std::unordered_map<QString, std::vector<QPoint>>>
            elementPositions = {
            {ElementCategory::OBSTACLE, {
                    {"FULL_FLOOR", {}},
                    {"LARGE_WOOD_FLOOR", {}},
                    {"LEFT_LADDER", {}},
                    {"LONG_PLATFORM", {}},
                    {"RIGHT_LADDER", {}},
                    {"SMALL_PLATFORM", {}},
                    {"WOOD_FLOOR", {}},
                    {"WOOD_LARGE_COLUMN", {}}
                                                }},
            {ElementCategory::ENEMY, {
                    {"TURTLES", {}},
                    {"SCHWARZENGUARDS", {}},
                    {"YELLOWMONS", {}}
                                             }},
            {ElementCategory::ITEM, {
                    {"GEMS", {}},
                    {"GOLD_COINS", {}},
                    {"SILVER_COINS", {}},
                    {"FOOD", {}}
                                            }},
            {ElementCategory::PLAYER, {
                    {"JAZZ", {}},
                    {"SPAZ", {}},
                    {"LORI", {}}
                                              }}
    };

    void createYAML(const QString& mapName);
};

#endif // LEVELEDITOR_H
