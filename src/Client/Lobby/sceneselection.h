#ifndef SCENESELECTION_H
#define SCENESELECTION_H

#include <QMainWindow>
#include <QVBoxLayout>

#include "../Monitors/QTMonitor.h"
#include "../Protocol/lobbyMessage.h"

#include "scenespriteswidget.h"

namespace Ui {
class SceneSelection;
}

class SceneSelection : public QMainWindow
{
    Q_OBJECT

    

public:
    explicit SceneSelection(QWidget *parent, QTMonitor& monitor, LobbyMessage& msg);
    ~SceneSelection();

private slots:
    void on_btnChoose_clicked();

    void on_btnBack_clicked();

private:
    Ui::SceneSelection *ui;
    QTMonitor& monitor;
    LobbyMessage& msg;
    SceneSpritesWidget* sceneSpritesWidget;
};

#endif // SCENESELECTION_H
