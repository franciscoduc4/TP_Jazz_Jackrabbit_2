#ifndef CHARACTERSELECTION_H
#define CHARACTERSELECTION_H

#include <QDialog>

#include "../../Common/Config/ClientConfig.h"
#include "../Protocol/Types/lobbyMessage.h"
#include "../client.h"
#include "./SelectWidgets/characterselectionwidget.h"

namespace Ui {
class CharacterSelection;
}

class CharacterSelection : public QDialog
{
    Q_OBJECT
    

public:
    explicit CharacterSelection(QWidget *parent, LobbyController& controller, LobbyMessage& msg, bool& clientJoinedGame);
    ~CharacterSelection();

private slots:
    void on_btnChoose_clicked();

    void on_btnBack_clicked();

private:
    Ui::CharacterSelection *ui;
    LobbyController& controller;
    LobbyMessage& msg;
    bool& clientJoinedGame;
    CharacterSelectionWidget* characterSelectionWidget;
};

#endif // CHARACTERSELECTION_H
