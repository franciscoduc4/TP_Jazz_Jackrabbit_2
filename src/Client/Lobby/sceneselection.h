#ifndef SCENESELECTION_H
#define SCENESELECTION_H

#include <QMainWindow>
#include <QVBoxLayout>

#include "../Protocol/lobbyMessage.h"
#include "../client.h"
#include "SelectScreens/scenespriteswidget.h"

namespace Ui {
class SceneSelection;
}

class SceneSelection : public QMainWindow
{
    Q_OBJECT

    

public:
    explicit SceneSelection(QWidget *parent, Client& client, LobbyMessage& msg, bool& clientJoinedGame);
    ~SceneSelection();

private slots:
    void on_btnChoose_clicked();

    void on_btnBack_clicked();

private:
    Ui::SceneSelection *ui;
    Client& client;
    LobbyMessage& msg;
    bool& clientJoinedGame;
    SceneSpritesWidget* sceneSpritesWidget;
};

#endif // SCENESELECTION_H
