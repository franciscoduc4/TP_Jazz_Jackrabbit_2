#ifndef SCENESELECTION_H
#define SCENESELECTION_H

#include <QDialog>
#include <QVBoxLayout>

#include "../../Common/Config/ClientConfig.h"
#include "../Protocol/Types/lobbyMessage.h"
#include "../client.h"
#include "SelectWidgets/scenespriteswidget.h"

namespace Ui {
class SceneSelection;
}

class SceneSelection: public QDialog {
    Q_OBJECT


public:
    explicit SceneSelection(QWidget* parent, LobbyController& controller, LobbyMessage& msg,
                            bool& clientJoinedGame);
    ~SceneSelection();

private slots:
    void on_btnChoose_clicked();

    void on_btnBack_clicked();

private:
    Ui::SceneSelection* ui;
    LobbyController& controller;
    LobbyMessage& msg;
    bool& clientJoinedGame;
    SceneSpritesWidget* sceneSpritesWidget;
};

#endif  // SCENESELECTION_H
