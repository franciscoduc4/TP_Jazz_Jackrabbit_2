#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H

#include <QButtonGroup>
#include <QDialog>
#include <QFile>
#include <QGraphicsBlurEffect>
#include <QMessageBox>
#include <QRadioButton>
#include <QVBoxLayout>

#include "../../Common/Config/ClientConfig.h"
#include "../../Common/Types/lobbyMessage.h"
#include "../client.h"
#include "./SelectWidgets/characterselectionwidget.h"

namespace Ui {
class CharacterSelection;
}

class CharacterSelection: public QDialog {
    Q_OBJECT


public:
    explicit CharacterSelection(QWidget* parent, LobbyController& controller, LobbyMessage& msg,
                                bool& clientJoinedGame);
    ~CharacterSelection();

private slots:
    void on_btnChoose_clicked();
    void on_btnBack_clicked();

private:
    Ui::CharacterSelection* ui;
    LobbyController& controller;
    LobbyMessage& msg;
    bool& clientJoinedGame;
    CharacterSelectionWidget* characterSelectionWidget;
    // QButtonGroup* buttonGroup;
};

#endif  // CHARACTERSELECTION_H
