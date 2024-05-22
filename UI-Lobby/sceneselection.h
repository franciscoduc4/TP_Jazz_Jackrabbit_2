#ifndef SCENESELECTION_H
#define SCENESELECTION_H

#include <QMainWindow>

namespace Ui {
class SceneSelection;
}

class SceneSelection : public QMainWindow
{
    Q_OBJECT

public:
    explicit SceneSelection(QWidget *parent = nullptr);
    ~SceneSelection();

private:
    Ui::SceneSelection *ui;
};

#endif // SCENESELECTION_H
