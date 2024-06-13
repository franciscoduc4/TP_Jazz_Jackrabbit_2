#ifndef MAPSELECTION_H
#define MAPSELECTION_H

#include <QDialog>
#include <QVBoxLayout>

#include "../../Common/Config/ClientConfig.h"
#include "../../Common/Types/lobbyMessage.h"
#include "../client.h"
#include "SelectWidgets/scenespriteswidget.h"

namespace Ui {
class MapSelection;
}

class MapSelection: public QDialog {
    Q_OBJECT


public:
    explicit MapSelection(QWidget* parent, LobbyController& controller, LobbyMessage& msg,
                            bool& clientJoinedGame);
    ~MapSelection();

private slots:
    void on_btnChoose_clicked();

    void on_btnBack_clicked();

private:
    Ui::MapSelection* ui;
    LobbyController& controller;
    LobbyMessage& msg;
    bool& clientJoinedGame;
    SceneSpritesWidget* sceneSpritesWidget;
};

#endif  // MAPSELECTION_H
