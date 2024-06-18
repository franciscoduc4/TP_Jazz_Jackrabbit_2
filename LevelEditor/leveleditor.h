#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCore>
#include <QPixmap>
#include <unordered_map>

#include <yaml-cpp/yaml.h>

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
    /*void onElementSelected(int index);
    void onAddElementClicked();
    void onRemoveElementClicked();*/
    void onSaveClicked();

private:
    Ui::LevelEditor *ui;
    QPixmap mapCanvas;
    std::unordered_map<QString, std::vector<QPoint>> elementData;
};

#endif // LEVELEDITOR_H
